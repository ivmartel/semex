// wrapping of the command line
#include "HelloMaskCLP.h"

// std
#include <iostream>
// ITK
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
// TheLib
#include <ApplyMaskImageFilter.h>
#include <ApplyMaskImageFilterParallel.h>
#include <CommandObserver.h>

// main method
int main( int argc, char* argv[] )
{
    // get the input arguments
    PARSE_ARGS;
	
	// Image type
    typedef itk::Image< unsigned char, 3 > ImageType;
    	
	// typedefs
	typedef itk::ImageFileReader< ImageType > ReaderType;
	typedef thelib::ApplyMaskImageFilter< ImageType > FilterType;
	typedef thelib::ApplyMaskImageFilterParallel< ImageType > FilterTypeParallel;
    typedef itk::ImageFileWriter< ImageType > WriterType;
    
    // image reader
    ReaderType::Pointer imageReader = ReaderType::New();
    imageReader->SetFileName( inputImage );
    
    // mask reader
    ReaderType::Pointer maskReader = ReaderType::New();
    maskReader->SetFileName( inputMask );
    
    // filter
    FilterTypeParallel::Pointer filter = FilterTypeParallel::New();
    filter->SetInput( imageReader->GetOutput() );
    filter->SetInput( 1, maskReader->GetOutput() );
    filter->SetInvertMask( invertMask );
    
    // writer
    WriterType::Pointer writer = WriterType::New();
    writer->SetInput( filter->GetOutput() );
    writer->SetFileName( outputImage );
    
    // progress observer
    thelib::CommandObserver::Pointer observer = thelib::CommandObserver::New();
    filter->AddObserver( itk::StartEvent(), observer );
    filter->AddObserver( itk::ProgressEvent(), observer );
    filter->AddObserver( itk::EndEvent(), observer );
    // information about the filter
    //filter->Print( std::cout );

    // run pipeline
    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & err )
    {
        std::cerr << "ExceptionObject caught !" << std::endl;
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
