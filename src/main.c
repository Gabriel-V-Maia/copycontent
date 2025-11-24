#include <stdio.h>
#include <stdlib.h>

int copy_to_clipboard(const char *text) {
    FILE *pipe = popen("wl-copy", "w");
    if (!pipe) {
        fprintf(stderr, "erro ao executar wl-copy\n");
        return 1;
    }

    fprintf(pipe, "%s", text);
    int status = pclose(pipe);

    if (status != 0) {
        fprintf(stderr, "wl-copy retornou erro\n");
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    return copy_to_clipboard(buffer);
}

