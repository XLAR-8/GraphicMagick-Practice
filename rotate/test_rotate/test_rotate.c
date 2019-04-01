//Example code to rotate using GraphicMagick 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>
#include <magick/image.h>
#include <sys/time.h>


int main ( int argc, char **argv )
{
  Image
  	*image_in = (Image *) NULL,
    *image_in_r = (Image *) NULL,
    *image_out = (Image *) NULL;

  int
    exit_status = 0;

  ImageInfo
    *image_info_in,
    *image_info_out;

  PixelPacket
  	bg_in;

  ExceptionInfo
    exception;


  InitializeMagick(NULL);
  image_info_in=CloneImageInfo((ImageInfo *) NULL);
  image_info_out=CloneImageInfo((ImageInfo *) NULL);
  GetExceptionInfo(&exception);

  image_info_in->size=AllocateString("250x250");
  image_info_in->colorspace  = TransparentColorspace;
  image_info_in->background_color.red = 0;
  image_info_in->background_color.green = MaxRGB;
  image_info_in->background_color.blue = 0;
  image_info_in->background_color.opacity = MaxRGB;
  image_info_in->matte_color.red = 0;
  image_info_in->matte_color.green = 0;
  image_info_in->matte_color.blue = MaxRGB;
  image_info_in->matte_color.opacity = MaxRGB;

  image_in = AllocateImage( image_info_in );
  if (image_in == (Image *) NULL)
    {
      CatchException(&exception);
      exit_status = 1;
      goto program_exit;
    }

  bg_in.red = MaxRGB;
  bg_in.green = 0;
  bg_in.blue = 0;
  bg_in.opacity = 0;
  SetImageColor( image_in, &bg_in );

  image_in_r = RotateImage( image_in, 30.0, &exception );

  (void) strcpy(image_in_r->filename, "rectangle.png");
  if (!WriteImage (image_info_in,image_in_r))
    {
      CatchException(&image_in->exception);
      exit_status = 1;
      goto program_exit;
    }

  image_info_out->size=AllocateString("500x500");
  image_info_out->depth = 8;
  image_info_out->colorspace  = RGBColorspace;
  image_info_out->background_color.red = (int)(MaxRGB/2);
  image_info_out->background_color.green = 0;
  image_info_out->background_color.blue = (int)(MaxRGB/2);
  image_info_out->background_color.opacity = 0;
  image_out = AllocateImage( image_info_out );
  if (image_out == (Image *) NULL)
    {
      CatchException(&exception);
      exit_status = 1;
      goto program_exit;
    }

  SetImageColor( image_out, &image_info_out->background_color );

  CompositeImage( image_out, OverCompositeOp, image_in_r, 1, 1 );

  (void) strcpy(image_out->filename, "composite.png");
  if (!WriteImage (image_info_out,image_out))
    {
      CatchException(&image_out->exception);
      exit_status = 1;
      goto program_exit;
    }

program_exit:

  if (image_out != (Image *) NULL)
    DestroyImage(image_out);

  if (image_in != (Image *) NULL)
    DestroyImage(image_in);

  if (image_in_r != (Image *) NULL)
    DestroyImage(image_in_r);

  if (image_info_out != (ImageInfo *) NULL)
    DestroyImageInfo(image_info_out);

  if (image_info_in != (ImageInfo *) NULL)
    DestroyImageInfo(image_info_in);

  DestroyMagick();

  return exit_status;
}
