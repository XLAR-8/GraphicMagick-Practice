#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wand/magick_wand.h>

int main(int argc,char **argv)
{
  MagickWand *magick_wand;
  MagickPassFail status = MagickPass;
  const char *infile;
  unsigned int is_opaque;

  if (argc != 2)
    {
      fprintf(stderr,"Usage: %s: infile\n",argv[0]);
      return 1;
    }

  infile=argv[1];

  // Initialize GraphicsMagick API
  InitializeMagick(*argv);

  // Allocate Wand handle
  magick_wand=NewMagickWand();

  // Read input image file
  if (status == MagickPass)
    {
      status = MagickReadImage(magick_wand,infile);
    }

  // Check if image is opaque
  if (status == MagickPass)
    {
      status = MagickIsOpaqueImage(magick_wand, &is_opaque);
    }

  if (status == MagickPass)
    {
      printf("%s is opaque: %s\n", infile, (!is_opaque ? "NO" : "YES"));
    }
  else
    {
      char *description;
      ExceptionType severity;

      description=MagickGetException(magick_wand,&severity);
      (void) fprintf(stderr,"%.1024s (severity %d)\n",
                     description,severity);
    }

  // Release Wand handle
  DestroyMagickWand(magick_wand);

  // Destroy GraphicsMagick API
  DestroyMagick();

  return (status == MagickPass ? 0 : 1);
}
