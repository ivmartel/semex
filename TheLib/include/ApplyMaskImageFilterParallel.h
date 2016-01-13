/**
* \file ApplyMaskImageFilterParallel.h
* \brief Definition of the thelib::ApplyMaskImageFilterParallel class.
*/
#ifndef THELIB_APPLYMASKIMAGEFILTERPARALLEL_H
#define THELIB_APPLYMASKIMAGEFILTERPARALLEL_H

// ITK
#include <itkImageToImageFilter.h>

// namespace
namespace thelib
{

/** 
* \brief Mask an input image (input 0) using a mask image (input 1) (parrallel).
* \ingroup TheLib
*/
template< class T >
class ApplyMaskImageFilterParallel : public itk::ImageToImageFilter<T,T>
{

public:

    //! Standard class typedefs.
    typedef ApplyMaskImageFilterParallel Self;
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
    ApplyMaskImageFilterParallel();

    //! Destructor: protect from instantiation.
    ~ApplyMaskImageFilterParallel();
    
    /**
    * Main method.
    * \param outputRegionForThread Image region to apply the filter to.
    * \param threadId The thread identifier.
    */
    void ThreadedGenerateData( 
        const typename itk::ImageSource<T>::OutputImageRegionType& outputRegionForThread, 
        itk::ThreadIdType threadId);

private:

    //! Copy constructor: purposely not implemented.
    ApplyMaskImageFilterParallel( const Self& filter);

    //! Assignement operator: purposely not implemented.
    void operator=( const Self& filter);
    
    //! Flag to invert the mask or not
    bool m_InvertMask;

}; // class ApplyMaskImageFilterParallel

} // namespace thelib

#endif //THELIB_APPLYMASKIMAGEFILTERPARALLEL_H
