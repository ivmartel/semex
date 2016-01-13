/**
* \file ApplyMaskImageFilter.h
* \brief Definition of the thelib::ApplyMaskImageFilter class.
*/
#ifndef THELIB_APPLYMASKIMAGEFILTER_H
#define THELIB_APPLYMASKIMAGEFILTER_H

// ITK
#include <itkImageToImageFilter.h>

//! \namespace thelib Main namespace.
namespace thelib
{

/** 
* \brief Mask an input image (input 0) using a mask image (input 1).
* \ingroup TheLib
*/
template< class T >
class ApplyMaskImageFilter : public itk::ImageToImageFilter<T,T>
{

public:

    //! Standard class typedefs.
    typedef ApplyMaskImageFilter Self;
    typedef itk::ImageToImageFilter<T,T> Superclass;
    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::SmartPointer<const Self> ConstPointer;

    //! Method for creation through the object factory.
    itkNewMacro(Self);
    
    //! Run-time type information (and related methods).
    itkTypeMacro(ApplyMaskImageFilter, ImageToImageFilter);
    
    //! Set the invert flag.
    itkSetMacro(InvertMask, bool);
    
    //! Get the invert flag.
    itkGetConstMacro(InvertMask, bool);
    
    /**
    * Print information about this class.
    * \param os The stream to output to.
    * \param indent The indent to apply to the output.
    */
    void PrintSelf(std::ostream& os, itk::Indent indent) const;

protected:

    //! Constructor: protect from instantiation.
    ApplyMaskImageFilter();

    //! Destructor: protect from instantiation.
    ~ApplyMaskImageFilter();
    
    //! Main method.
    void GenerateData();

private:

    //! Copy constructor: purposely not implemented.
    ApplyMaskImageFilter( const Self& filter);

    //! Assignement operator: purposely not implemented.
    void operator=( const Self& filter);
    
    //! Flag to invert the mask or not
    bool m_InvertMask;

}; // class ApplyMaskImageFilter

} // namespace thelib

#endif //THELIB_APPLYMASKIMAGEFILTER_H
