#include "../include/dds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GLuint load_dds(const char* image_path) {
    unsigned char header[124];
    FILE *fp;

    fp = fopen(image_path, "rb");
    if (fp == NULL)
        return 0;

    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    fread(&header, 124, 1, fp);
    unsigned int height = *(unsigned int*)&(header[8 ]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linear_size = *(unsigned int*)&(header[16]);
    unsigned int mipmap_count = *(unsigned int*)&(header[24]);
    unsigned int four_cc = *(unsigned int*)&(header[80]);

    unsigned char * buffer;
    unsigned int bufsize;

    bufsize = mipmap_count > 1 ? linear_size * 2 : linear_size;
    buffer = (unsigned char *) malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    fclose(fp);

    unsigned int components = (four_cc == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(four_cc)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmap_count > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipmap_count && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer);

    return textureID;
}
