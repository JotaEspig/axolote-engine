#include "axolote/gl/framebuffer.hpp"
#include "axolote/utils.hpp"

namespace axolote {

namespace gl {

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &_id);
    debug("Framebuffer created: %u", _id);
}

} // namespace gl

} // namespace axolote
