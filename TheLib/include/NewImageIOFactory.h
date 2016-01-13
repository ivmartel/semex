/**
* \file NewImageIOFactory.h
* \brief Definition of the thelib::NewImageIOFactory class.
*/
#ifndef THELIB_NEWIMAGEIOFACTORY_H
#define THELIB_NEWIMAGEIOFACTORY_H

// ITK
#include <itkObjectFactoryBase.h>

// namespace
namespace thelib
{

/**
* \brief Create instances of NewImageIO objects using an object factory.
* \ingroup TheLib
*/
class NewImageIOFactory : public itk::ObjectFactoryBase
{

public: 
 
    //! Standard class typedefs.
    typedef NewImageIOFactory Self;
    typedef ObjectFactoryBase Superclass;
    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::SmartPointer<const Self> ConstPointer;

    //! ITK source version.
    virtual const char* GetITKSourceVersion(void) const;
    
    //! Provide a description of this IO factory.
    virtual const char* GetDescription(void) const;

    //! Method for creation through the object factory.
    itkFactorylessNewMacro(Self);
    
    //! Run-time type information (and related methods).
    itkTypeMacro(NewImageIOFactory, ObjectFactoryBase);

    //! Register one factory of this type.
    static void RegisterOneFactory(void)
    {
        NewImageIOFactory::Pointer factory = NewImageIOFactory::New();
        ObjectFactoryBase::RegisterFactory(factory);
    }

protected:

    //! Constructor: protect from instantiation.
    NewImageIOFactory();
    
    //! Desctructor: protect from instantiation.
    ~NewImageIOFactory();

private:

    //! Copy constructor: purposely not implemented.
    NewImageIOFactory(const Self&);
    
    //! Assignement operator: purposely not implemented.
    void operator=(const Self&);

}; // class NewImageIOFactory
  
} // end namespace thelib

#endif // THELIB_NEWIMAGEIOFACTORY_H
