#include "utils.hpp"

const std::string HELP_NOTE =   "\n----------This program will help you check your files integrity----------\n\n"
                                "After creating your file you can calculate its checksum and save it to file.\n"
                                "When files integrity check is needed, you can calculate it again and compair with alraedy created.\n\n"
                                "There are several options to run this program with:\n\n"
                                "(1)\t--help - print helping note\n"
                                "(2)\t--calc <file_name> - calculate checksum for your file\n"
                                "(3)\t--check <file_name> - check your file integrity\n"
                                "(4, 5)\t[--calc, --check] --cs-file <checksum-filename> - specify path for your checksum file\n\n";

int main(int argc, char** argv)
{
    if (!Utils::isValidCommand(argc, argv)) {
        std::cerr << WrongCommandException().what();
        return 1;
    }
    std::string filename, scFilename;
    try {
        if (Utils::isFirstCommand(argc, argv)) {

            std::cout << HELP_NOTE;

        } else if (Utils::isSecondCommand(argc, argv)) {

            filename = argv[2];
            scFilename = filename + ".crc";
            std::string crc = Utils::calculateCRC32(filename);
            Utils::writeToFile(scFilename, crc);

        } else if (Utils::isThirdCommand(argc, argv)) {

            filename = argv[2];
            if (Utils::checkFileIntegrity(filename)) {
                std::cout << "File integrity check passed.\n";
            }
            else {
                throw CheckFailedException();
            }

        } else if (Utils::isFourthCommand(argc, argv)) {

            filename = argv[2];
            scFilename = argv[4];
            std::string crc = Utils::calculateCRC32(filename);
            Utils::writeToFile(scFilename, crc);

        } else if (Utils::isFifthCommand(argc, argv)){

            filename = argv[2];
            scFilename = argv[4];
            if (Utils::checkFileIntegrity(filename, scFilename)) {
                std::cout << "File integrity check passed.\n";
            }
            else {
                throw CheckFailedException();
            }

        }
    } catch (const FileOpenException& ex) {
        std::cerr << ex.what();
        return 1;
    } catch (const CheckFailedException& ex) {
        std::cerr << ex.what();
        return 1;
    } catch (const WrongCommandException& ex) {
        std::cerr << ex.what();
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception";
        return 1;
    }
	return 0;
}
