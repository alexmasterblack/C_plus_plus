#include <memory>

class BufferedReader {
 private:
    PackageStream* new_stream;
    std::shared_ptr<char[]> buffer;
    std::shared_ptr<char[]> support_buffer;
    int32_t support_count = 0;
    int32_t check = 0;

 public:
    explicit BufferedReader(PackageStream* stream) {
        new_stream = stream;
        std::shared_ptr<char[]> sup(new char[stream->PackageLen()]);
        support_buffer = sup;
        buffer = sup;
    }
    int32_t Read(char* output_buffer, int32_t buffer_len) {
        int32_t real_buffer_lenght = 0, result_package = 0;
        do {
            if (check == 0 || (support_count == 0 && check == 1)) {
                result_package = new_stream->ReadPackage(buffer.get());
                check = 0;
            }
            if (check == 1) {
                memmove(buffer.get(), support_buffer.get(), support_count);
                result_package = support_count;
                support_count = 0;
            }
            if (buffer_len >= result_package) {
                memmove(output_buffer + real_buffer_lenght, buffer.get(),
                result_package);
                real_buffer_lenght += result_package;
            } else {
                int32_t difference = buffer_len - real_buffer_lenght;
                memmove(output_buffer + real_buffer_lenght,
                buffer.get(), difference);
                memmove(support_buffer.get(), buffer.get() + difference,
                result_package - difference);
                real_buffer_lenght += difference;
                support_count = result_package - difference;
                check = 1;
                break;
            }
        } while (result_package > 0);
        return real_buffer_lenght;
    }
};
