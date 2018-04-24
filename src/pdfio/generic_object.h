#pragma once

namespace pdfio
{
   
/*! \brief Identifies object type by the tipeId_.
 * 
 *  The struct GenericObject along with GenericObjectAdaptor represents 
 *  "variant" concept.
 *  The constructor GenericObjectAdaptor<T>::GenericObjectAdaptor() calls 
 *  GenericObject constructor 
 *  using GenericObject::TypeId<T>() as an argument. 
 *  Since GenericObject::TypeId<T>() is not defined
 *  it forces client to define GenericObject::TypeId for each particular type.
    @code
    class A{...};
    class B{...};
    enum class Type
    {
      kA,
      kB,
    };
    int GenericObject::TypeId<A>(){return Type::kA;}
    int GenericObject::TypeId<B>(){return Type::kB;}
    @endcode
 *  The primary use cases are the PDF Dictionary, PDF Array and PDF Indirect 
 *  Object that might hold any PDF objects.
 *  Since GenericObject::typeId_ is initialized by GenericObject::TypeId<T>() 
 *  for any T, client knows how to convert
 *  GenericObject to GenericObjectAdaptor<T>. 
 *  GenericObject has virtual destructor.
    @code
    A a;
    B b;
    std::vector<std::shared_ptr<pdfio::GenericObject>> objects;
    objects.push_back(std::static_pointer_cast<pdfio::GenericObject>(
      std::make_shared<GenericObjectAdaptor<A>>(a)));
    objects.push_back(std::static_pointer_cast<pdfio::GenericObject>(
      std::make_shared<GenericObjectAdaptor<B>>(b)));
    for(auto object : objects)
    {
      if(object->typeId_ == Type::kA)
      {
         static_pointer_cast<GenericObjectAdaptor<A>>(*object).object_....
      }
      else
      {
         static_pointer_cast<GenericObjectAdaptor<B>>(*object).object_....
      }
    }
    @endcode
 */
struct GenericObject
{
   /*! \brief Contructs the GenericObject with the typeId.*/
   inline GenericObject(int typeId)
   : typeId_(typeId)
   {
      
   }
   /*! \brief Destructs the GenericObject.*/
   virtual ~GenericObject() = default;
   /*! \brief Returns type id of the T.*/
   template <typename T> static int TypeId();
   /*! \brief Identifies the GenericObject type id.*/
   const int typeId_;
};
/*! \brief Holds an object of the type T.*/
template <typename T> struct GenericObjectAdaptor: GenericObject
{
   /*! \brief Contructs the GenericObjectAdaptor with the object.*/
   GenericObjectAdaptor(const T &object)
   : GenericObject(GenericObject::TypeId<T>())
   , object_(object)
   {
      
   }
   /*! \brief Internal the T object.*/
   T object_;
};

} // namespace pdfio
