#include "read_name.h"
#include "read_indirect_reference.h"
#include "read_dictionary.h"
#include "read_hexstring.h"
#include "read_array.h"
#include "read_stream.h"
#include "read_document_catalog.h"
#include "read_outline_tree.h"
#include "read_literalstring.h"
#include "read_string.h"
#include "read_document_pages_tree.h"
#include "read_info.h"
#include "pdfio/pdf1_0/real.h"
#include "pdfio/read_generic_object.h"

using namespace pdfio;
using namespace pdfio::pdf1_0;

REGISTER_READ_HANDLER_FOR_TYPE(Name);
REGISTER_READ_HANDLER_FOR_TYPE(Integer);
REGISTER_READ_HANDLER_FOR_TYPE(IndirectReference);
REGISTER_READ_HANDLER_FOR_TYPE(Dictionary);
typedef Array<HexString> HexStringArray;
REGISTER_READ_HANDLER_FOR_TYPE(HexStringArray);
REGISTER_READ_HANDLER_FOR_TYPE(Real);
typedef Stream::Filter StreamFilter;
REGISTER_READ_HANDLER_FOR_TYPE(StreamFilter);
REGISTER_READ_HANDLER_FOR_TYPE(Stream);
typedef Array<Integer> IntegerArray;
REGISTER_READ_HANDLER_FOR_TYPE(IntegerArray);
REGISTER_READ_HANDLER_FOR_TYPE(DocumentCatalog);
typedef Array<IndirectReference> IndirectReferenceArray;
REGISTER_READ_HANDLER_FOR_TYPE(IndirectReferenceArray);
typedef Array<Real> RealArray;
REGISTER_READ_HANDLER_FOR_TYPE(RealArray);
typedef Array<Name> NameArray;
REGISTER_READ_HANDLER_FOR_TYPE(NameArray);
REGISTER_READ_HANDLER_FOR_TYPE(OutlineTree);
typedef OutlineTree::Entry OutlineTreeEntry;
REGISTER_READ_HANDLER_FOR_TYPE(OutlineTreeEntry);
REGISTER_READ_HANDLER_FOR_TYPE(LiteralString);
REGISTER_READ_HANDLER_FOR_TYPE(String);
REGISTER_READ_HANDLER_FOR_TYPE(DocumentPagesTree);
REGISTER_READ_HANDLER_FOR_TYPE(Info);
