// Desenvolva um programa em C que lê o conteúdo de um arquivo no formato da imagem escolhida por você 
// e exibe todas as informações do arquivo (assinatura, cabeçalho, dados, etc.) em modo texto.
// Referencia em C: https://pt.stackoverflow.com/questions/210877/leitura-de-uma-imagem-bitmap

#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

#pragma pack(push, 1)
struct BMP_Header {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

int main() {
    // Abrir o arquivo BMP em modo binário
    fstream bmpFile("image.bmp", ios::in | ios::binary);

    
    if (!bmpFile.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    // Ler o cabeçalho do BMP
    BMP_Header header;
    bmpFile.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Extrair informações do cabeçalho
    int width = header.biWidth;
    int height = header.biHeight;
    int bitDepth = header.biBitCount;

    // Exibir informações do cabeçalho
    cout << "Cabeçalho do BMP:" << endl;
    cout << " - Largura: " << width << endl;
    cout << " - Altura: " << height << endl;
    cout << " - Profundidade de bits: " << bitDepth << endl;

    char signature[2];
    bmpFile.seekg(0, ios::beg);
    bmpFile.read(signature, 2);

    // Exibir a assinatura
    cout << "Assinatura: " << signature[0] << signature[1] << endl;

    int bytesPerPixel = bitDepth / 8;
    int rowStride = width * bytesPerPixel;
    unsigned char* imageData = new unsigned char[rowStride * height];
    bmpFile.seekg(header.bfOffBits, ios::beg);
    bmpFile.read(reinterpret_cast<char*>(imageData), rowStride * height);

    // Exibir os dados da imagem
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int offset = y * rowStride + x * bytesPerPixel;
            unsigned char blue = imageData[offset];
            unsigned char green = imageData[offset + 1];
            unsigned char red = imageData[offset + 2];
            cout << "(" << static_cast<int>(red) << "," << static_cast<int>(green) << "," << static_cast<int>(blue) << ") ";
        }
        cout << endl;
    }

    // Liberar memória alocada
    delete[] imageData;

    return 0;
}
