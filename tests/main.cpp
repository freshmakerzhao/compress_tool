// tests/main.cpp
#include "ArchiveTool.hpp"
#include <iostream>
#include <fstream>
#include <vector>
int main() {
    try {
        Tool::ArchiveTool tool;

        // 写入字符串到内存缓冲区
        std::string inputText = "This is some sample text to compress.";
        std::vector<Tool::byte_t> buffer;
        tool.string_to_byte(inputText, buffer);

        // 压缩 buffer 内容为 test_output.7z
        tool.compress(buffer, "test_output.7z", "test.txt");
        std::cout << "✅ 压缩完成: test_output.7z\n";

        // 从 .7z 中解压出 buffer 内容
        std::vector<Tool::byte_t> outBuffer;
        tool.extract("test_output.7z", outBuffer);

        // 输出解压后内容
        std::string restoredText = tool.byte_to_string(outBuffer);
        std::cout << "✅ 解压结果: " << restoredText << std::endl;

    }
    catch (const std::exception& ex) {
        std::cerr << "❌ 异常: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
