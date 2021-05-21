#include "src/parser/parser.h"
#include "src/writer/writer.h"

int main(int argc, char const *argv[])
{
    t_tag* parsedDoc = parser("test.xml");

    printf("\n");

    printTag(parsedDoc);

    printf("\n");
    a_document doc = initDoc();
    writeTexteEnrichi(doc, parsedDoc);
    printf("\n");
    return 0;
}
