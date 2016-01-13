/**
* \file ApplyMaskImageFilterTests.cpp
* \brief Implementation of tests of the thelib::ApplyMaskImageFilter class.
*/

// ITK
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
// TheLib
#include <ApplyMaskImageFilter.h>

// anonymous namespace
namespace
{

//! Remove a file
bool removeFile( const std::string& filename )
{
    if( remove( filename.c_str() ) != 0 ) 
    {
        std::cerr << "Error deleting file: '" << filename << "'" << std::endl;
        return false;
    }
    return true;
}

//! @test Test the mask filter.
bool RunMask( const std::string& testDataPath, bool invertMask )
{
	// paths
	const std::string inputFilename = testDataPath + "/MRHead.mhd";
	const std::string maskFilename = testDataPath + "/MRHead-label.mhd";
	const std::string outputFilename = "output.mhd";
	const std::string outputImgFilename = "output.raw";
	   
	// typedefs
    typedef itk::Image< unsigned char, 3 > ImageType;
	typedef itk::ImageFileReader< ImageType > ReaderType;
	typedef thelib::ApplyMaskImageFilter< ImageType > FilterType;
    typedef itk::ImageFileWriter< ImageType > WriterType;
    
    // image reader
    ReaderType::Pointer imageReader = ReaderType::New();
    imageReader->SetFileName( inputFilename );
    
    // mask reader
    ReaderType::Pointer maskReader = ReaderType::New();
    maskReader->SetFileName( maskFilename );
    
    // filter
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput( imageReader->GetOutput() );
    filter->SetInput( 1, maskReader->GetOutput() );
    filter->SetInvertMask( invertMask );

    // writer
    WriterType::Pointer writer = WriterType::New();
    writer->SetInput( filter->GetOutput() );
    writer->SetFileName( outputFilename );

    // run pipeline
    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & err )
    {
        std::cerr << "ExceptionObject caught !" << std::endl;
        std::cerr << err << std::endl;
        return false;
    }
    
	// Check content of the output image
	ImageType::ConstPointer output = filter->GetOutput();
	
	// check pixel
	ImageType::IndexType index;
	index[0] = 128;
	index[1] = 128;
	index[2] = 65;
	if( invertMask )
	{
	    if ( output->GetPixel( index ) != 58 ) 
	    {
	        std::cerr << "Not the expected pixel value (58), got: "<< (int)output->GetPixel( index ) << std::endl;
	        return false;
	    }
	}
	else
	{
	    if ( output->GetPixel( index ) != 0 ) 
	    {
	        std::cerr << "Not the expected pixel value (0), got: "<< (int)output->GetPixel( index ) << std::endl;
	        return false;
	    }
	}
	
    // remove generated test file
    if( !removeFile( outputFilename ) ) return false;
    if( !removeFile( outputImgFilename ) ) return false;

    // success
    return true;
}

} // anonymous namespace

/**
* Test runner
*/
int main (int argc, char *argv[])
{
    // test data path
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " test_data_path" << std::endl;
        return EXIT_FAILURE;
    }
    const std::string testDataPath = argv[1];

    // run tests
    if( !RunMask( testDataPath, false ) ) 
    {
        std::cerr << "Failed the RunMask test with no inversion." << std::endl;
        return EXIT_FAILURE;
    }
    if( !RunMask( testDataPath, true ) ) 
    {
        std::cerr << "Failed the RunMask test with inversion." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "All tests passed!" << std::endl;
    return EXIT_SUCCESS;
}
