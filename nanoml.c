#include "src/parser/parser.h"
#include "src/writer/writer.h"

int main(int argc, char const *argv[])
{
    if (argc == 1 || argc == 3 || argc > 4) {
        fprintf(stderr, "ERROR : Invalid number of arguments : try : nanoml FILENAME ([-o DESTINATION]|[--out DESTINATION])\n");
        exit(-1);
    }

    FILE* destination = stdout;

    if (argc == 4) {
        if (compareStr(argv[2], "-o") || compareStr(argv[2], "--out")) {
            destination = fopen(argv[3], "w");
        }
    }

    a_tag  parsedDoc = parser(argv[1]);

    // ? Uncomment to debug :
    // printTag(parsedDoc);
    // printf("\n");


    a_document doc = initDoc(destination);
    writeTexteEnrichi(doc, parsedDoc);

    if (destination != stdout) {
        fclose(destination);
    }
    return 0;
}
