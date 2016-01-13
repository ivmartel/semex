// wrapping of the command line
#include "HelloImageCLP.h"

// std
#include <iostream>
// ITK
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkThresholdImageFilter.h>

// anonymous namespace
namespace
{

void GetImageType (const std::string& fileName,
    itk::ImageIOBase::IOPixelType &pixelType,
    itk::ImageIOBase::IOComponentType &componentType)
{
    typedef itk::Image<unsigned char, 3> ImageType;
    itk::ImageFileReader<ImageType>::Pointer imageReader =
        itk::ImageFileReader<ImageType>::New();
    imageReader->SetFileName(fileName.c_str());
    imageReader->UpdateOutputInformation();

    pixelType = imageReader->GetImageIO()->GetPixelType();
    componentType = imageReader->GetImageIO()->GetComponentType();
}
   
/**
* DoIt.
* Apply a threshold filter on the input image.
*/
template<class T> int DoIt( int argc, char * argv[], T )
{
    // get the input arguments
    PARSE_ARGS;
    
    // Image type
    typedef itk::Image< T, 3 > ImageType;
    	
    // typedefs
    typedef itk::ImageFileReader< ImageType > ReaderType;
    typedef itk::ThresholdImageFilter< ImageType > FilterType;
    typedef itk::ImageFileWriter< ImageType > WriterType;
    
    // image reader
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( inputImage );
    
    // filter
    typename FilterType::Pointer filter = FilterType::New();
    filter->SetInput( reader->GetOutput() );
    filter->ThresholdBelow(thresholdBelowValue);
    
    // writer
    typename WriterType::Pointer writer = WriterType::New();
    writer->SetInput( filter->GetOutput() );
    writer->SetFileName( outputImage );

    // progress
    //itk::PluginFilterWatcher watchReader(reader, "Read Volume", CLPProcessInformation);
    //itk::PluginFilterWatcher watchFilter(filter, "Threshold image", CLPProcessInformation);
    //itk::PluginFilterWatcher watchWriter(writer, "Write Volume", CLPProcessInformation);        
    
    // run pipeline
    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject& err )
    {
        std::cerr << "ExceptionObject caught !" << std::endl;
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

} // end of anonymous namespace

// main method
int main( int argc, char* argv[] )
{
    // get the input arguments
    PARSE_ARGS;

    itk::ImageIOBase::IOPixelType pixelType;
    itk::ImageIOBase::IOComponentType componentType;
    
    try
    {
        // get the data type to run the DoIt method with the correct type
        GetImageType (inputImage, pixelType, componentType);

        // This filter handles all types
        switch (componentType)
        {
            case itk::ImageIOBase::UCHAR:
                return DoIt( argc, argv, static_cast<unsigned char>(0));
                break;
            case itk::ImageIOBase::CHAR:
                return DoIt( argc, argv, static_cast<char>(0));
                break;
            case itk::ImageIOBase::USHORT:
                return DoIt( argc, argv, static_cast<unsigned short>(0));
                break;
            case itk::ImageIOBase::SHORT:
                return DoIt( argc, argv, static_cast<short>(0));
                break;
            case itk::ImageIOBase::UINT:
                return DoIt( argc, argv, static_cast<unsigned int>(0));
                break;
            case itk::ImageIOBase::INT:
                return DoIt( argc, argv, static_cast<int>(0));
                break;
            case itk::ImageIOBase::ULONG:
                return DoIt( argc, argv, static_cast<unsigned long>(0));
                break;
            case itk::ImageIOBase::LONG:
                return DoIt( argc, argv, static_cast<long>(0));
                break;
            case itk::ImageIOBase::FLOAT:
                return DoIt( argc, argv, static_cast<float>(0));
                break;
            case itk::ImageIOBase::DOUBLE:
                return DoIt( argc, argv, static_cast<double>(0));
                break;
            case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
            default:
                std::cout << "unknown component type" << std::endl;
                break;
        }
    }
    catch( itk::ExceptionObject& excep)
    {
        std::cerr << argv[0] << ": exception caught !" << std::endl;
        std::cerr << excep << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

