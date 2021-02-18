//
// Created by Percebe32 on 2/13/2021.
//

#ifndef QUESTER_QTEXTURE_HXX
#define QUESTER_QTEXTURE_HXX

#include <d3d11.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <Graphics/stb_image.h>

class IQTexture {
public:
    IQTexture() = default;
    virtual ~IQTexture() = default;

     virtual bool LoadTextureDX11(
            ID3D11Device* device,
            const char* filename,
            ID3D11ShaderResourceView** out_srv,
            int* out_width,
            int* out_height);
};

#endif //QUESTER_QTEXTURE_HXX
