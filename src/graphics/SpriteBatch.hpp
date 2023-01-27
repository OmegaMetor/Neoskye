#pragma once

#include "Vector2.hpp"
#include "content/Sprite.hpp"
#include "util/Types.hpp"
#include <memory>

namespace neoskye {
namespace graphics {

struct DrawData {
    DrawData(content::Sprite& spr, Vector2<usize> pos);
    content::Sprite& spr;
    Vector2<usize> pos;
};

/// <summary>
/// Allows you to draw sprites in one big batch
/// </summary>
class SpriteBatch {
  public:
    /// <summary>
    /// Creates a SpriteBatch, use `neoskye::content::GetSpriteBatch` instead
    /// </summary>
    SpriteBatch();
    // TODO: add more overloads
    /// <summary>
    /// Submits a sprite for drawing
    /// </summary>
    void Submit(content::Sprite& spr, Vector2<usize> pos);
    /// <summary>
    /// Gets the draw data, is only used internally
    /// </summary>
    std::vector<DrawData>& GetDrawData();
    /// <summary>
    /// Removes all the draw data
    /// </summary>
    void Flush();

  private:
    std::vector<DrawData> queue;
};

} // namespace graphics
} // namespace neoskye