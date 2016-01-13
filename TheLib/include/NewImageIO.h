/**
* \file NewImageIO.h
* \brief Definition of the thelib::NewImageIO class.
*/
#ifndef THELIB_NEWIMAGEIO_h
#define THELIB_NEWIMAGEIO_h

// ITK
#include "itkImageIOBase.h"

// namespace
namespace thelib
{

/**
* \brief ImageIO object for reading and writing 'New' images.
* \ingroup TheLib
*/
class NewImageIO : public itk::ImageIOBase
{

public:

    //! Standard class typedefs.
    typedef NewImageIO Self;
    typedef ImageIOBase Superclass;
    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::SmartPointer<const Self> ConstPointer;

    //! Method for creation through the object factory.
    itkNewMacro(Self);

    //! Run-time type information (and related methods).
    itkTypeMacro(NewImageIO, ImageIOBase);

    /*-------- This part of the interface deals with reading data. ------ */

    /** Determine the file type. Returns true if this ImageIO can read the
    * file specified. */
    virtual bool CanReadFile(const char*);

    /** Set the spacing and dimension information for the set filename. */
    virtual void ReadImageInformation();

    /** Reads the data from disk into the memory buffer provided. */
    virtual void Read(void* buffer);

    /*-------- This part of the interfaces deals with writing data. ----- */

    /** Determine the file type. Returns true if this ImageIO can write the
    * file specified. */
    virtual bool CanWriteFile(const char*);

    /** Writes the spacing and dimentions of the image.
    * Assumes SetFileName has been called with a valid file name. */
    virtual void WriteImageInformation();

    /** Writes the data to disk from the memory buffer provided. Make sure
    * that the IORegion has been set properly. */
    virtual void Write(const void* buffer);
    
    
    std::string GetExtension( const std::string& filename ) const;
    std::string GetRootName( const std::string& filename ) const;
    std::string GetHeaderFileName( const std::string& filename ) const;
    std::string GetImageFileName( const std::string& filename ) const;


protected:

    //! Constructor: protect from instantiation.
    NewImageIO();

    //! Desctructor: protect from instantiation.
    ~NewImageIO();
    
    //! Print information about this class.
    void PrintSelf(std::ostream& os, itk::Indent indent) const;

private:

    //! Copy constructor: purposely not implemented.
    NewImageIO(const Self&);
    
    //! Assignement operator: purposely not implemented.
    void operator=(const Self&);
    
    std::string m_Extension;
    std::string m_FormatName;
    std::string m_FormatVersion;

}; // class NewImageIO

} // end namespace thelib

#endif // THELIB_NEWIMAGEIO_h
