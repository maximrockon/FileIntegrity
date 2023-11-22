#include "utils.hpp"
#include <sstream>
#include <iomanip>
#include <zlib.h>

std::string Utils::calculateCRC32(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw FileOpenException();
    }

    std::ostringstream ss;
    uLong crc = crc32(0L, Z_NULL, 0);

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        crc = crc32(crc, reinterpret_cast<Bytef*>(buffer), sizeof(buffer));
    }
    crc = crc32(crc, reinterpret_cast<Bytef*>(buffer), file.gcount());
    file.close();

    ss << std::hex << std::setw(8) << std::setfill('0') << crc;
    return ss.str();
}

void Utils::writeToFile(const std::string& filename, const std::string& value) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw FileOpenException();
    }
    file << value;
    file.close();
}

bool Utils::checkFileIntegrity(const std::string& filename, const std::string& scFilename) {
    std::string newCRC;
    try {
        newCRC = calculateCRC32(filename);
    } catch (const FileOpenException& ex) {
        throw ex;
    }

    std::string scFilenameCopy = scFilename;
    if (scFilename == std::string()) {
        scFilenameCopy = filename + ".crc";
    }
    std::ifstream savedCRCFile(scFilenameCopy);
    if (!savedCRCFile.is_open()) {
        throw FileOpenException();
    }


    std::string savedCRC;
    savedCRCFile >> savedCRC;
    savedCRCFile.close();

    return newCRC == savedCRC;
}

bool Utils::isFirstCommand(int argc, char* argv[]) {
    return (argc == 2) && (strcmp(argv[1], "--help") == 0);
}

bool Utils::isSecondCommand(int argc, char* argv[]) {
    return (argc == 3) && (strcmp(argv[1], "--calc") == 0 );
}

bool Utils::isThirdCommand(int argc, char* argv[]) {
    return (argc == 3) && (strcmp(argv[1], "--check") == 0);
}

bool Utils::isFourthCommand(int argc, char* argv[]) {
    return (argc == 5)
        && (strcmp(argv[1], "--calc") == 0)
        && (strcmp(argv[3], "--cs-file") == 0);
}

bool Utils::isFifthCommand(int argc, char* argv[]) {
    return (argc == 5)
        && (strcmp(argv[1], "--check") == 0)
        && (strcmp(argv[3], "--cs-file") == 0);
}


bool Utils::isValidCommand(int argc, char* argv[]) {
    return Utils::isFirstCommand(argc, argv)
        || Utils::isSecondCommand(argc, argv)
        || Utils::isThirdCommand(argc, argv)
        || Utils::isFourthCommand(argc, argv)
        || Utils::isFifthCommand(argc, argv);
}