#pragma once

namespace axolote {

struct RenderState {
    /** If true, the object will draw **/
    bool should_draw = true;
    /** If true, the object won't update, no matter what **/
    bool is_paused = false;
    /** If true, the Scene pause rule won't be able to make the object not
     * update. Sometimes we want to bypass the scene pause rule with this pause
     * rule, e.g. a light attached to the camera where the entire scene is
     * pause, simulating a time stop, but the torchlight from the character
     * should still work **/
    bool ignore_scene_pause_rule = false;
};

} // namespace axolote
