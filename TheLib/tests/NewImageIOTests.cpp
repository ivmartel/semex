/**
* \file NewImageIOTests.cpp
* \brief Tests of the thelib::NewImageIO class.
*/

// ITK
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkObjectFactoryBase.h>
// TheLib
#include <NewImageIO.h>
#include <NewImageIOFactory.h>

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

//! @test Test the reading of data.
bool TestReadWrite(const std::string& testDataPath)
{
	// paths
	const std::string inputFilename = testDataPath + "/MRHead.new";
	const std::string outputFilename = "output.new";
	const std::string outputImgFilename = "output.raw";
	   
	// typedefs
    typedef itk::Image< unsigned char, 3 > ImageType;
	typedef itk::ImageFileReader< ImageType > ReaderType;
	typedef itk::ImageFileWriter< ImageType > WriterType;
    
    // reader
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( inputFilename );
    
    // register our IO factory
    itk::ObjectFactoryBase::RegisterFactory( thelib::NewImageIOFactory::New() ); 
    // or could be set per reader/writer
    //thelib::NewImageIO::Pointer imageIO = thelib::NewImageIO::New();
    //reader->SetImageIO( imageIO );
    
    // writer
    WriterType::Pointer writer = WriterType::New();
    writer->SetInput( reader->GetOutput() );
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
    
	// check content of the read image
	ImageType::ConstPointer output = reader->GetOutput();

	// size
	ImageType::SizeType sizeTheo;
	sizeTheo[0] = 130;
	sizeTheo[1] = 256;
	sizeTheo[2] = 256;
	for ( unsigned int i = 0; i < 3; ++i )
	{
	    if ( sizeTheo[i] != output->GetLargestPossibleRegion().GetSize()[i] ) 
	    {
	        std::cerr << "Not the expected size." << std::endl;
	        //return false;
	    }
	}
	
	// origin
	ImageType::PointType originTheo;
	originTheo[0] = 0;
	originTheo[1] = 0;
	originTheo[2] = 0;
	for ( unsigned int i = 0; i < 3; ++i )
	{
	    if ( originTheo[i] != output->GetOrigin()[i] ) 
	    {
	        std::cerr << "Not the expected origin." << std::endl;
	        return false;
	    }
	}
	
	// spacing
	ImageType::SpacingType spacingTheo;
	spacingTheo[0] = 1.3;
	spacingTheo[1] = 1;
	spacingTheo[2] = 1;
	for ( unsigned int i = 0; i < 3; ++i )
	{
	    if ( spacingTheo[i] != output->GetSpacing()[i] ) 
	    {
	        std::cerr << "Not the expected spacing." << std::endl;
	        return false;
	    }
	}
	
	// random pixel
	ImageType::IndexType index;
	index[0] = 128;
	index[1] = 128;
	index[2] = 65;
	if ( output->GetPixel( index ) != 51 ) 
	{
	    std::cerr << "Not the expected pixel value (51): " << int(output->GetPixel( index )) << std::endl;
	    return false;
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
    if( !TestReadWrite(testDataPath) ) return EXIT_FAILURE;

    std::cout << "All tests passed!" << std::endl;
    return EXIT_SUCCESS;
}
