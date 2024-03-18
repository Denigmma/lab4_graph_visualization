#pragma once
#include "Function_draw_graph.h"
void saveBMP(const std::vector<std::vector<int>>& image) {
	std::ofstream outFile("output.bmp", std::ios::binary);
	if (!outFile) {
		std::cout << "Failed to open output file." << std::endl;
		return;
	}
	int width = image.size();
	int height = image[0].size();
	int padding = (4 - (width * 3) % 4) % 4;
	int fileSize = 54 + (3 * width + padding) * height;

	// Заголовок BMP файла
	unsigned char bmpHeader[54] = {
		'B', 'M',         // Сигнатура
		fileSize & 0xFF, (fileSize >> 8) & 0xFF, (fileSize >> 16) & 0xFF, (fileSize >> 24) & 0xFF, // Размер файла
		0, 0, 0, 0,       // Зарезервированное поле
		54, 0, 0, 0,      // Смещение до данных
		40, 0, 0, 0,      // Размер заголовка
		width & 0xFF, (width >> 8) & 0xFF, (width >> 16) & 0xFF, (width >> 24) & 0xFF, // Ширина
		height & 0xFF, (height >> 8) & 0xFF, (height >> 16) & 0xFF, (height >> 24) & 0xFF, // Высота
		1, 0,             // Количество цветовых плоскостей
		24, 0,            // Бит на пиксель
		0, 0, 0, 0,       // Метод сжатия (0 = без сжатия)
		0, 0, 0, 0,       // Размер изображения в байтах (можно 0 для безсжатия)
		0, 0, 0, 0,       // Горизонтальное разрешение, пиксель на метр (не важно)
		0, 0, 0, 0,       // Вертикальное разрешение, пиксель на метр (не важно)
		0, 0, 0, 0,       // Количество используемых цветов в изображении (не важно)
		0, 0, 0, 0        // Количество основных цветов (не важно)
	};

	outFile.write(reinterpret_cast<char*>(bmpHeader), 54);

	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			unsigned char color = static_cast<unsigned char>(image[x][y]);
			outFile.write(reinterpret_cast<char*>(&color), sizeof(color));
			outFile.write(reinterpret_cast<char*>(&color), sizeof(color));
			outFile.write(reinterpret_cast<char*>(&color), sizeof(color));
		}
		for (int p = 0; p < padding; ++p) {
			outFile.put(0);
		}
	}
	outFile.close();
}