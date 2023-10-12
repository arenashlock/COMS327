#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

/* Do not modify write_pgm() or read_pgm() */
int write_pgm(char *file, void *image, uint32_t x, uint32_t y)
{
  FILE *o;

  if (!(o = fopen(file, "w"))) {
    perror(file);

    return -1;
  }

  fprintf(o, "P5\n%u %u\n255\n", x, y);

  /* Assume input data is correctly formatted. *
   * There's no way to handle it, otherwise.   */

  if (fwrite(image, 1, x * y, o) != (x * y)) {
    perror("fwrite");
    fclose(o);

    return -1;
  }

  fclose(o);

  return 0;
}

/* A better implementation of this function would read the image dimensions *
 * from the input and allocate the storage, setting x and y so that the     *
 * user can determine the size of the file at runtime.  In order to         *
 * minimize complication, I've written this version to require the user to  *
 * know the size of the image in advance.                                   */
int read_pgm(char *file, void *image, uint32_t x, uint32_t y)
{
  FILE *f;
  char s[80];
  unsigned i, j;

  if (!(f = fopen(file, "r"))) {
    perror(file);

    return -1;
  }

  if (!fgets(s, 80, f) || strncmp(s, "P5", 2)) {
    fprintf(stderr, "Expected P6\n");

    return -1;
  }

  /* Eat comments */
  do {
    fgets(s, 80, f);
  } while (s[0] == '#');

  if (sscanf(s, "%u %u", &i, &j) != 2 || i != x || j != y) {
    fprintf(stderr, "Expected x and y dimensions %u %u\n", x, y);
    fclose(f);

    return -1;
  }

  /* Eat comments */
  do {
    fgets(s, 80, f);
  } while (s[0] == '#');

  if (strncmp(s, "255", 3)) {
    fprintf(stderr, "Expected 255\n");
    fclose(f);

    return -1;
  }

  if (fread(image, 1, x * y, f) != x * y) {
    perror("fread");
    fclose(f);

    return -1;
  }

  fclose(f);

  return 0;
}

int main(int argc, char *argv[])
{
  uint8_t image[1024][1024];
  uint8_t out[1024][1024];

  // Kernal for the vertical edge detection
  int K_x[3][3] = {{-1, 0, 1}, 
                   {-2, 0, 2},
                   {-1, 0, 1}};

  // Kernal for the horizontal edge detection
  int K_y[3][3] = {{-1, -2, -1},
                   {0, 0, 0},
                   {1, 2, 1}};
  
  // Read in the first user-given argument (filename) and make image
  read_pgm(argv[1], image, 1024, 1024);

  // Counting variables for the image matrix and the kernels
  int r, c, j, i;

  // 0-1024 rows
  for(r = 0; r < 1024; r++){
    // 0-1024 columns
    for(c = 0; c < 1024; c++){
      // Final value for the output image pixel
      double O = 0;

      // Results of the kernel multiplied by the image pixels
      int O_x = 0;
      int O_y = 0;

      // 0-3 rows
      for(j = 0; j < 3; j++){
        // 0-3 columns
        for(i = 0; i < 3; i++){
          // If statement for detecting a pixel on the edge (negative number or greater than 1024)
          if((r - 1 + j >= 0) && (r - 1 + j <= 1024) && (c - 1 + i >= 0) && (c - 1 + i <= 1024)){
            // Take old results and add new
            O_x = O_x + ((int) image[r - 1 + j][c - 1 + i] * K_x[j][i]);
            O_y = O_y + ((int) image[r - 1 + j][c - 1 + i] * K_y[j][i]);
          }
        }
      }

      // Plugging in values into given equation
      O = sqrt((O_x * O_x) + (O_y * O_y));

      // Assigning pixel with resultant O value
      out[r][c] = (int) O;
    }
  }

  // Take the generated out matrix and write it to "sobel.pgm"
  write_pgm("sobel.pgm", out, 1024, 1024);
  
  return 0;
}