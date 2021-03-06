/**
* \file ApplyMaskImageFilter.cpp
* \brief Implementation of the thelib::ApplyMaskImageFilter class.
*/
#include "ApplyMaskImageFilter.h"

// ITK
#include <itkImage.h>
#include <itkImageRegionIterator.h>
#include <itkImageRegionConstIterator.h>

namespace thelib
{

template< class T >
ApplyMaskImageFilter< T >::ApplyMaskImageFilter()
: m_InvertMask( false )
{
    // input iamge and mask
    this->SetNumberOfRequiredInputs( 2 );
}

template< class T >
ApplyMaskImageFilter< T >::~ApplyMaskImageFilter()
{
}

template< class T >
void ApplyMaskImageFilter< T >::PrintSelf(std::ostream& os, itk::Indent indent) const
{
    Superclass::PrintSelf(os,indent);
    os << indent << "InvertMask: " << m_InvertMask << std::endl;
}

template< class T >
void ApplyMaskImageFilter< T >::GenerateData()
{
    // Allocate output
    this->AllocateOutputs();

    // Get the input and output pointers;
    typename T::ConstPointer inputImage = this->GetInput( 0 ); 
    typename T::ConstPointer maskImage = this->GetInput( 1 );   
    typename T::Pointer outputImage = this->GetOutput();
    
    // check input
    if( inputImage.IsNull() )
    {
        throw itk::ExceptionObject(__FILE__, __LINE__, "GenerateData: no input data.", ITK_LOCATION);
    }
    if( maskImage.IsNull() )
    {
        throw itk::ExceptionObject(__FILE__, __LINE__, "GenerateData: no nask data.", ITK_LOCATION);
    }

    // Iterators on requested region (default region is complete image)
    itk::ImageRegionConstIterator<T> itImage( inputImage, inputImage->GetRequestedRegion() );
    itk::ImageRegionConstIterator<T> itMask( maskImage, maskImage->GetRequestedRegion() );
    itk::ImageRegionIterator<T> itOut( outputImage, outputImage->GetRequestedRegion() );

    // support progress methods/callbacks
    const unsigned long totalPixels = inputImage->GetRequestedRegion().GetNumberOfPixels();
    unsigned long updateVisits = totalPixels / 10;
    if( updateVisits < 1 ) updateVisits = 1;

    // Initialise vars
    itImage.GoToBegin();
    itMask.GoToBegin();
    unsigned long i = 0;

    // Loop through requested region
    for( itOut.GoToBegin(); !itOut.IsAtEnd(); ++itOut )
    {
        // Progress
        if( !(i % updateVisits ) )
        {
            this->UpdateProgress((float)i / (float)totalPixels);
        }
        if( this->GetAbortGenerateData() )
        {
            return;
        }

        // Mask operation
        if( m_InvertMask )
        {
            if( itMask.Get() != 0 )
            {
                itOut.Set( static_cast< typename T::PixelType >( 0 ) ); 
            }
            else
            {
                itOut.Set( static_cast< typename T::PixelType >( itImage.Get() ) );
            }
        }
        else
        {
            if( itMask.Get() != 0 )
            {
                itOut.Set( static_cast< typename T::PixelType >( itImage.Get() ) );
            }
            else
            {
                itOut.Set( static_cast< typename T::PixelType >( 0 ) );
            }
        }
        // increment iterators
        ++i;
        ++itMask;
        ++itImage;
    }
}

// explicit instantiation
template class ApplyMaskImageFilter< itk::Image< unsigned char, 3 > >;

} // namespace thelib
