// http://web.stanford.edu/class/cs107/assign1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FRAGMENT_OPEN       '{'
#define FRAGMENT_CLOSE      '}'
#define FRAGMENT_MAX_LEN    1000
#define FRAGMENT_MAX_COUNT  20000

/*
 * Fragment
 */
typedef struct {
    int length;
    char* string;
} Fragment;

static inline
Fragment fragment_create(const char* string, int length)
{
    Fragment f = { .length = length, .string = malloc(length + 1) };
    memcpy(f.string, string, length + 1);
    return f;
}

static inline
void fragment_swap(Fragment* a, Fragment* b)
{
    Fragment tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline
void fragment_replace(Fragment* f, char* string, int length)
{
    free(f->string);
    f->string = string;
    f->length = length;
}

static inline
void fragment_destroy(Fragment* f)
{
    free(f->string);
}


/*
 * Fragment Holder
 */
typedef struct {
    int count;
    Fragment fragments[FRAGMENT_MAX_COUNT];
} FragmentHolder;

FragmentHolder* fragmentholder_create(void)
{
    FragmentHolder* fh = calloc(1, sizeof(FragmentHolder));
    return fh;
}

static inline
int fragmentholder_append(FragmentHolder* fh, const char* string, int length)
{
    if (fh->count == FRAGMENT_MAX_COUNT) {
        return -1;
    }
    fh->fragments[fh->count++] = fragment_create(string, length);
    return 0;
}

static inline
Fragment* fragmentholder_meld_one_off(FragmentHolder* fh,
                                      Fragment* keep,
                                      Fragment* remove)
{
    Fragment* last = &fh->fragments[--fh->count];
    if (last == keep) {
        keep = remove;
    }
    if (last != remove) {
        fragment_swap(last, remove);
    }
    fragment_destroy(last);
    return keep;
}

void fragmentholder_destroy(FragmentHolder* fh)
{
    for (int i = 0; i < fh->count; ++i) {
        fragment_destroy(&fh->fragments[i]);
    }
    free(fh);
}


/*
 * File Input
 */
FragmentHolder* get_fragments(const char* filename)
{
    FILE* f = fopen(filename, "r");
    FragmentHolder* fh = fragmentholder_create();

    char* buffer = malloc(FRAGMENT_MAX_LEN + 1);
    int c = '\0';
    while (c != EOF) {
        char* bufptr = buffer;

        while ((c = fgetc(f)) != FRAGMENT_OPEN && c != EOF) {
        }
        if (c == EOF) {
            break;
        }

        while ((c = fgetc(f)) != FRAGMENT_CLOSE && c != EOF) {
            if (bufptr - buffer <= FRAGMENT_MAX_LEN) {
                *(bufptr++) = (char)c;
            }
            else {
                exit(EXIT_FAILURE);
            }
        }

        if (c == FRAGMENT_CLOSE) {
            *bufptr = '\0';
            fragmentholder_append(fh, buffer, bufptr - buffer);
            bufptr = buffer;
        }
    }
    free(buffer);
    fclose(f);
    return fh;
}


/*
 * Match
 */
int greedy_match(const Fragment* longer,
                 const Fragment* shorter,
                 int min_acceptable_length,
                 int* max_overlap_longer_pos,
                 int* max_overlap_shorter_pos)
{
    *max_overlap_longer_pos = 0;
    *max_overlap_shorter_pos = 0;

    char* pos = strstr(longer->string, shorter->string);
    if (pos) {
        *max_overlap_longer_pos = pos - longer->string;
        return shorter->length;
    }

    int max_overlap = 0;
    for (int offset = longer->length - min_acceptable_length;
         offset > -shorter->length + min_acceptable_length;
         --offset) {

        int longer_pos = offset;
        int shorter_pos = 0;
        int length;

        if (offset > longer->length - shorter->length) {
            length = longer->length - offset;
        }
        else if (offset >= 0) {
            offset = 0;
            continue;
        }
        else {
            longer_pos = 0;
            shorter_pos = -offset;
            length = shorter->length + offset;
        }

        if (max_overlap > length) {
            break;
        }

        if (!memcmp(longer->string + longer_pos,
                    shorter->string + shorter_pos, length)) {
            max_overlap = length;
            *max_overlap_longer_pos = longer_pos;
            *max_overlap_shorter_pos = shorter_pos;
        }
    }
    return max_overlap;
}


/*
 * Pair
 */
typedef struct {
    Fragment* longer;
    Fragment* shorter;
    int longer_pos;
    int shorter_pos;
    int overlap;
} Pair;

Pair get_max_overlap_pair(FragmentHolder* fh)
{
    int max_overlap = 0;
    Pair max_pair = { 0 };

    Fragment* endptr = &fh->fragments[fh->count];
    for (Fragment* ptri = fh->fragments; ptri < endptr - 1; ++ptri) {
        for (Fragment* ptrj = ptri + 1; ptrj < endptr; ++ptrj) {
            Fragment* longer = (ptri->length >= ptrj->length) ? ptri : ptrj;
            Fragment* shorter = (ptri->length >= ptrj->length) ? ptrj : ptri;

            if (shorter->length <= max_overlap) {
                continue;
            }

            int longer_pos;
            int shorter_pos;
            int overlap = greedy_match(longer, shorter, max_overlap + 1,
                                       &longer_pos, &shorter_pos);

            if (overlap > max_overlap) {
                Pair p = { longer, shorter, longer_pos, shorter_pos, overlap };
                max_pair = p;
                max_overlap = overlap;
            }
        }
    }
    return max_pair;
}

void merge_pair(FragmentHolder* fh, Pair* p)
{
    if (!p->overlap) {
        return;
    }

    Fragment* begin = (p->longer_pos != 0) ? p->longer : p->shorter;
    Fragment* end = (p->longer_pos != 0) ? p->shorter : p->longer;
    int merged_length = begin->length + end->length - p->overlap;

    char* merged = malloc(merged_length + 1);
    memcpy(merged, begin->string, begin->length);
    memcpy(merged + begin->length,
           end->string + p->overlap,
           end->length - p->overlap + 1);

    Fragment* longer = fragmentholder_meld_one_off(fh, p->longer, p->shorter);
    fragment_replace(longer, merged, merged_length);
}


/*
 * Main
 */
int main(int argc, char* argv[])
{
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    FragmentHolder* fh = get_fragments(argv[1]);

    while (fh->count > 1) {
        int count_before = fh->count;

        Pair max_pair = get_max_overlap_pair(fh);
        merge_pair(fh, &max_pair);

        if (fh->count == count_before) {
            printf("Unable to reassemble into one fragment.\n");
            break;
        }
    }

    if (fh->count > 0) {
        printf("%s\n", fh->fragments[0].string);
    }

    fragmentholder_destroy(fh);
}
