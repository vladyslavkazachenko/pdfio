#pragma once

#include "document_page_tree_node.h"
#include "array.h"
#include "integer.h"
#include "indirect_reference.h"

namespace pdfio
{
  
namespace pdf1_0
{
  
/*! \brief PDF page object.*/
class DocumentPage: public DocumentPageTreeNode
{
public:
  /*! \brief Page resource "dictionary" for Font, Encoding, FontDescriptor, ColorSpace, XObject.*/
  typedef std::map<Name, IndirectReference> ResourceDictionary;
  /*! \brief Page ProcSet resources.*/
  class ProcSet: public Array<Name>{};
  /*! \brief Page resources.*/
  class Resources: public Dictionary
  {
  public:
    /*! \brief Checks whether the resources has "Font".*/
    inline bool hasFonts() const
    {
      return contains(Name("Font"));
    }
    /*! \brief Returns value of the resources' "Font".*/
    inline const ResourceDictionary &fonts() const
    {
      return get<ResourceDictionary>(Name("Font"));
    }
    /*! \brief Returns value of the resources' "Font".*/
    inline ResourceDictionary &fonts()
    {
      return get<ResourceDictionary>(Name("Font"));
    }
    /*! \brief Checks whether the resources has "ProcSet".*/
    inline bool hasProcSet() const
    {
      return contains(Name("ProcSet"));
    }
    /*! \brief Returns value of the resources' "ProcSet".*/
    inline const ProcSet &procSet() const
    {
      return get<ProcSet>(Name("ProcSet"));
    }
    /*! \brief Returns value of the resources' "ProcSet".*/
    inline ProcSet &procSet()
    {
      return get<ProcSet>(Name("ProcSet"));
    }
    /*! \brief Initializes base dictionar.*/
    inline void prepare4Read()
    {
      insert<ResourceDictionary>(Name("Font"));
      insert<ProcSet>(Name("ProcSet"));
    }
  };
  /*! \brief Constructs the page initializing base dictionary.*/
  inline DocumentPage()
  : DocumentPageTreeNode(Name("Page"))
  {
    insert<Array<Integer>>(Name("MediaBox"));
    get<Array<Integer>>(Name("MediaBox")).resize(4);
    insert<IndirectReference>(Name("Parent"));
    insert<Resources>(Name("Resources"));
  }
  /*! \brief Returns value of the page's "MediaBox".*/
  inline const Array<Integer> &mediaBox() const
  {
    return get<Array<Integer>>(Name("MediaBox"));
  }
  /*! \brief Returns value of the page's "MediaBox".*/
  inline Array<Integer> &mediaBox()
  {
    return get<Array<Integer>>(Name("MediaBox"));
  }
  /*! \brief Returns value of the page's "Parent".*/
  inline const IndirectReference &parent() const
  {
    return get<IndirectReference>(Name("Parent"));
  }
  /*! \brief Returns value of the page's "Parent".*/
  inline IndirectReference &parent()
  {
    return get<IndirectReference>(Name("Parent"));
  }
  /*! \brief Returns value of the page's "Resources".*/
  inline const Resources &resources() const
  {
    return get<Resources>(Name("Resources"));
  }
  /*! \brief Returns value of the page's "Resources".*/
  inline Resources &resources()
  {
    return get<Resources>(Name("Resources"));
  }
  /*! \brief Checks whether the page has "Contents".*/
  inline bool hasContents() const
  {
    return contains(Name("Contents"));
  }
  /*! \brief Returns value of the page's "Contents".*/
  inline const IndirectReference &contents() const
  {
    return get<IndirectReference>(Name("Contents"));
  }
  /*! \brief Returns value of the page's "Contents".*/
  inline IndirectReference &contents()
  {
    if(!hasContents())
    {
      insert<IndirectReference>(Name("Contents"));
    }
    return get<IndirectReference>(Name("Contents"));
  }
  /*! \brief Checks whether the page has "CropBox".*/
  inline bool hasCropBox() const
  {
    return false;
  }
  /*! \brief Checks whether the page has "Rotate".*/
  inline bool hasRotate() const
  {
    return false;
  }
  /*! \brief Checks whether the page has "Thumb".*/
  inline bool hasThumb() const
  {
    return contains(Name("Thumb"));
  }
  /*! \brief Returns value of the page's "Thumb".*/
  inline const IndirectReference &thumb() const
  {
    return get<IndirectReference>(Name("Thumb"));
  }
  /*! \brief Returns value of the page's "Thumb".*/
  inline IndirectReference &thumb()
  {
    if(!hasThumb())
    {
      insert<IndirectReference>(Name("Thumb"));
    }
    return get<IndirectReference>(Name("Thumb"));
  }
  /*! \brief Checks whether the page has "Annots".*/
  inline bool hasAnnots() const
  {
    return contains(Name("Annots"));
  }
  /*! \brief Returns value of the page's "Annots".*/
  inline const Array<IndirectReference> &annots() const
  {
    return get<Array<IndirectReference>>(Name("Annots"));
  }
  /*! \brief Returns value of the page's "Annots".*/
  inline Array<IndirectReference> &annots()
  {
    if(!hasAnnots())
    {
      insert<Array<IndirectReference>>(Name("Annots"));
    }
    return get<Array<IndirectReference>>(Name("Annots"));
  }
  /*! \brief Initializes base dictionary with required and optional entries.*/
  inline bool prepare4Read()
  {
    insert<Name>(Name("Type"));
    insert<Array<Integer>>(Name("MediaBox"));
    get<Array<Integer>>(Name("MediaBox")).resize(4);
    insert<IndirectReference>(Name("Parent"));
    insert<Resources>(Name("Resources"));
    insert<IndirectReference>(Name("Contents"));
    insert<IndirectReference>(Name("Thumb"));
    insert<Array<IndirectReference>>(Name("Annots"));
  }
};

}

}