#include <stdio.h>
#include <stdlib.h>

void snail(long w, long h, void (ret)(long, void*), void *data)
{
    long i, l = 0, r = w - 1, t = 0, b = h - 1;

    while (1) {
        if (t > b)
            break;

        for (i = l; i <= r; i++)
            ret(t * w + i + 1, data);

        t++;

        if (l > r)
            break;

        for (i = t; i <= b; i++)
            ret(i * w + r + 1, data);

        r--;

        if (t > b)
            break;

        for (i = r; i >= l; i--)
            ret(b * w + i + 1, data);

        b--;

        if (l > r)
            break;

        for (i = b; i >= t; i--)
            ret(i * w + l + 1, data);

        l++;
    }
}

struct print_data
{
    long w;
    int d, c;
};

static int parse(long *w, long *h, int argc, char *argv[])
{
    char *err;

    if (argc != 3)
        return -1;

    *w = strtol(argv[1], &err, 0);

    if (err && *err)
        return -1;

    *h = strtol(argv[2], &err, 0);

    if (err && *err)
        return -1;

    return 0;
}

static void print_init(struct print_data *p, long w, long h)
{
    long n = w * h;
    int d = 1;

    while (n > 9)
        d++, n /= 10;

    p->w = w;
    p->d = d;
    p->c = 0;
}

static void print(long v, void *data)
{
    struct print_data *p = (struct print_data *) data;

    printf("%*ld%c", p->d, v, (p->c++, p->c %= p->w) ? ' ' : '\n');
}

int main(int argc, char *argv[])
{
    long w, h, i, j;
    struct print_data pd;

    if (parse(&w, &h, argc, argv) < 0)
        return 1;

    printf("%ld %ld\n\n", w, h);

    print_init(&pd, w, h);

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            print(i * w + j + 1, &pd);

    printf("\n");
    snail(w, h, print, &pd);

    return 0;
}
