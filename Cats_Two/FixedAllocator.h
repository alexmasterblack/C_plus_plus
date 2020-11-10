#include <vector>

template <typename Tp>
class FixedAllocator {
  PageAllocator page_allocator_;
  uint64_t page_size;
  std::vector<Tp*> memory;

 public:
  explicit FixedAllocator(std::uint64_t page_size)
      : page_allocator_(page_size * sizeof(Tp)), page_size(page_size) {}
  Tp* Allocate() {
    if (memory.empty()) {
      Tp* place = static_cast<Tp*>(page_allocator_.Allocate());
      for (uint64_t i = 0; i < page_size; i++) {
        memory.push_back(place++);
      }
    }
    Tp* free = memory.back();
    memory.pop_back();
    return free;
  }
  void Deallocate(Tp* p) { memory.push_back(p); }
  const PageAllocator& InnerAllocator() const noexcept {
    return page_allocator_;
  }
};
