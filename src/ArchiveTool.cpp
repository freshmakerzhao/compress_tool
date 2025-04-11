#include "bit7z/bitfilecompressor.hpp"
#include "bit7z/bitmemcompressor.hpp"
#include "bit7z/bitfileextractor.hpp"
#include "bit7z/bitextractor.hpp"
#include "bit7z/bit7z.hpp"
#include "bit7z/bitoutputarchive.hpp"
#include "ArchiveTool.h"
#include <filesystem>

using namespace bit7z;
namespace Tool {
    const BitInOutFormat& format = BitFormat::SevenZip;
#ifdef _WIN32
    Bit7zLibrary lib{ "7zip.dll" };
#elif defined(__linux__)
    Bit7zLibrary lib{ "./bit7z/lib/SecuEngine.so" };
#endif
    BitFileExtractor extractor(lib, format);
    BitMemCompressor mem_compressor(lib, format);
    BitFileCompressor file_compressor(lib, format);

    std::vector<byte_t> ArchiveTool::extract(const std::string& inArchive, std::vector<byte_t>& outBuffer) {
        extractor.extract(inArchive, outBuffer);
        return outBuffer;
    }

    std::vector<byte_t> ArchiveTool::extractWithPassword(const std::string& inArchive, std::vector<byte_t>& outBuffer, std::string mPassword) {
        extractor.setPassword(mPassword);
        extractor.extract(inArchive, outBuffer);
        return outBuffer;
    }

    void ArchiveTool::compress(const std::vector<byte_t>& buffer,
                                                 const std::string& outFile,
                                                 const std::string& fileName) {
        std::filesystem::path outPath(outFile);
        std::error_code error;

        if (std::filesystem::exists(outPath, error)) {
            if (!std::filesystem::remove(outPath, error)) {
                throw BitException("Failed to delete the old archive file", error, outFile);
            }
        }

        bit7z::BitOutputArchive outputArchive{ mem_compressor, outFile };
        outputArchive.addFile(buffer, fileName);
        outputArchive.compressTo(outFile);
    }

    void ArchiveTool::compressWithPassword(const std::vector<byte_t>& buffer, const std::string& outFile, const std::string& fileName, std::string mPassword) {
        std::filesystem::path outPath(outFile);
        std::error_code error;
        if (std::filesystem::exists(outPath, error)) {
            const OverwriteMode overwriteMode = OverwriteMode::Overwrite;
            if (overwriteMode == OverwriteMode::Overwrite && !std::filesystem::remove(outPath, error)) {
                throw BitException("Failed to delete the old archive file", error, outFile);
            }
            // cout << error << endl;
        }

        mem_compressor.setPassword(mPassword);
        BitOutputArchive outputArchive{ mem_compressor, outFile };
        outputArchive.addFile(buffer, fileName);
        outputArchive.compressTo(outFile);

    }
    void ArchiveTool::compressWithPassword(const std::vector<byte_t>& buffer, std::ostream& outStream, const std::string& fileName, std::string mPassword) {
        mem_compressor.setPassword(mPassword);
        BitOutputArchive outputArchive{ mem_compressor };
        outputArchive.addFile(buffer, fileName);
        outputArchive.compressTo(outStream);

    }
    auto to_tstring2(const std::string& str) -> tstring {
        return tstring(str.begin(), str.end());
    }
    std::vector<tstring> convert_to_tstring(const std::vector<std::string>& input) {
        std::vector<tstring> output;
        for (const auto& str : input) {
            output.push_back(to_tstring2(str));
        }
        return output;
    }
    void compressWithPassword(const std::vector<std::string>& inpaths, std::ostream& outStream, const std::string& mPassword) {
        file_compressor.setPassword(mPassword);
        file_compressor.setOverwriteMode(OverwriteMode::Overwrite);
        file_compressor.compress(convert_to_tstring(inpaths), outStream);
    }
    void compressWithPassword(const std::vector<std::string>& inpaths, const std::string& outFile, const std::string& mPassword) {
        file_compressor.setPassword(mPassword);
        file_compressor.setOverwriteMode(OverwriteMode::Overwrite);
        file_compressor.compressFiles(convert_to_tstring(inpaths), outFile);
    }

    std::vector<byte_t> ArchiveTool::string_to_byte(const std::string& data, std::vector<byte_t>& buffer) {
        buffer.insert(buffer.end(), data.begin(), data.end());
        return buffer;
    }
    std::string ArchiveTool::byte_to_string(const std::vector<byte_t>& buffer) {
        return std::string(buffer.begin(), buffer.end());
    }
}