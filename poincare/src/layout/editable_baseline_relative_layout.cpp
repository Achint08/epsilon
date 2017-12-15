#include "editable_baseline_relative_layout.h"
#include <poincare/expression_layout_cursor.h>
#include <string.h>
#include <assert.h>

namespace Poincare {

bool EditableBaselineRelativeLayout::moveLeft(ExpressionLayoutCursor * cursor) {
  // Case: Left of the indice.
  // Go from the indice to the base.
  if (m_indiceLayout
      && cursor->pointedExpressionLayout() == m_indiceLayout
      && cursor->position() == ExpressionLayoutCursor::Position::Left)
  {
    assert(m_baseLayout != nullptr);
    cursor->setPointedExpressionLayout(m_baseLayout);
    cursor->setPosition(ExpressionLayoutCursor::Position::Right);
    return true;
  }
  // Case: Left of the base.
  // Ask the parent.
  if (m_baseLayout
      && cursor->pointedExpressionLayout() == m_baseLayout
      && cursor->position() == ExpressionLayoutCursor::Position::Left)
  {
    cursor->setPointedExpressionLayout(this);
    if (m_parent) {
      return m_parent->moveLeft(cursor);
    }
    return false;
  }
  assert(cursor->pointedExpressionLayout() == this);
  // Case: Right.
  // Go to the indice.
  if (cursor->position() == ExpressionLayoutCursor::Position::Right) {
    assert(m_indiceLayout != nullptr);
    cursor->setPointedExpressionLayout(m_indiceLayout);
    return true;
  }
  // Case: Left.
  // Ask the parent.
  assert(cursor->position() == ExpressionLayoutCursor::Position::Left);
  if (m_parent) {
    return m_parent->moveLeft(cursor);
  }
  return false;
}

bool EditableBaselineRelativeLayout::moveRight(ExpressionLayoutCursor * cursor) {
  // Case: Right of the base.
  // Go from the base to the indice.
  if (m_baseLayout
      && cursor->pointedExpressionLayout() == m_baseLayout
      && cursor->position() == ExpressionLayoutCursor::Position::Right)
  {
    assert(m_indiceLayout != nullptr);
    cursor->setPointedExpressionLayout(m_indiceLayout);
    cursor->setPosition(ExpressionLayoutCursor::Position::Left);
    return true;
  }
  // Case: Right of the indice.
  // Go Right.
  if (m_indiceLayout
      && cursor->pointedExpressionLayout() == m_indiceLayout
      && cursor->position() == ExpressionLayoutCursor::Position::Right)
  {
    cursor->setPointedExpressionLayout(this);
    return true;
  }
  assert(cursor->pointedExpressionLayout() == this);
  // Case: Left.
  // Go to the base and move Right.
  if (cursor->position() == ExpressionLayoutCursor::Position::Left) {
    assert(m_baseLayout != nullptr);
    cursor->setPointedExpressionLayout(m_baseLayout);
    return m_baseLayout->moveRight(cursor);
  }
  // Case: Right.
  // Ask the parent.
  assert(cursor->position() == ExpressionLayoutCursor::Position::Right);
  cursor->setPointedExpressionLayout(this);
  if (m_parent) {
    return m_parent->moveRight(cursor);
  }
  return false;
}


}

