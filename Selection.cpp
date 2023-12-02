#include "Main.h"
#include "UI.h"

template<>
Selection<string>::~Selection()
{
  for(long i{0}; i < static_cast<long>(m_choices.size()); ++i)
  {
    delete m_choices[i];
    m_choices[i] = nullptr;
    --mem;
  }
}

template <>
void Selection<string>::render_item(const long & x, const long & y, const long & item_index, Fnt* font) const
{
  if(item_index >= 0 && item_index < static_cast<long>(m_choices.size()))
  {
    font->render_text(*m_choices[item_index], x, y);
  }
}

template <>
void Selection<string>::update_input(Cursor* cursor, World* world)
{
  m_show_cursor = m_queue_show_cursor;
  m_show_menu = m_queue_show_menu;
  
  if(m_render_mode == "Items")
  {
    for(long i{0}; i < static_cast<long>(m_choices.size()); ++i)
    {
      delete m_choices[i];
      m_choices[i] = nullptr;
      --mem;
    }
    m_choices = to_pointers(world->get_items());
  }
  if(m_render_mode == "Key Items")
  {
    for(long i{0}; i < static_cast<long>(m_choices.size()); ++i)
    {
      delete m_choices[i];
      m_choices[i] = nullptr;
      --mem;
    }
    m_choices = to_pointers(world->get_key_items());
  }
    if(m_render_mode == "Stats")
  {
    for(long i{0}; i < static_cast<long>(m_choices.size()); ++i)
    {
      delete m_choices[i];
      m_choices[i] = nullptr;
      --mem;
    }
    vector<string> choices{STAT_STRINGS};
    m_choices = to_pointers(choices);
  }

  if(m_show_cursor == true)
  {
    if(m_focus_x + m_focus_y * m_columns >= static_cast<long>(m_choices.size()))
    {
      if(m_focus_x != 0)
      {
        --m_focus_x;
      }
      else if(m_focus_y != 0)
      {
        --m_focus_y;
        if(m_focus_y < m_display_start)
        {
          --m_display_start;
        }
      }
    }
    if(IsKeyPressed(KEY_UP) == true)
    {
      long m_focus_y_temp{max(m_focus_y - 1, static_cast<long>(0))};
      if(m_focus_x + m_focus_y_temp * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_y = max(m_focus_y - 1, static_cast<long>(0));
        if(m_focus_y < m_display_start)
        {
          --m_display_start;
        }
      }
    }
  
    if(IsKeyPressed(KEY_DOWN) == true)
    {
      long m_focus_y_temp{min(m_focus_y + 1, m_max_rows - 1)};
      if(m_focus_x + m_focus_y_temp * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_y = min(m_focus_y + 1, m_max_rows - 1);
        if(m_focus_y > m_display_start + m_display_rows - 1)
        {
          ++m_display_start;
        }
      }
    }
  
    if(IsKeyPressed(KEY_LEFT) == true)
    {
      long m_focus_x_temp{max(m_focus_x - 1, static_cast<long>(0))};
      if(m_focus_x_temp + m_focus_y * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_x = max(m_focus_x - 1, static_cast<long>(0));
      }
    }

    if(IsKeyPressed(KEY_RIGHT) == true)
    {
      long m_focus_x_temp{min(m_focus_x + 1, m_columns - 1)};
      if(m_focus_x_temp + m_focus_y * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_x = min(m_focus_x + 1, m_columns - 1);
      }
    }

    if(IsKeyPressed(KEY_Z) == true)
    {
      on_click();
    }
    cursor->set_destination(m_x + m_spacing_x * m_focus_x, m_y + m_spacing_y * (m_focus_y - m_display_start));
    m_highlighted_item = m_focus_x + m_focus_y * m_columns;
  }
}

template <>
void Selection<Player_Summary>::update_input(Cursor* cursor, World* world)
{
  m_show_cursor = m_queue_show_cursor;
  m_show_menu = m_queue_show_menu;

  if(m_show_cursor == true)
  {
    if(m_focus_x + m_focus_y * m_columns >= static_cast<long>(m_choices.size()))
    {
      if(m_focus_x != 0)
      {
        --m_focus_x;
      }
      else if(m_focus_y != 0)
      {
        --m_focus_y;
        if(m_focus_y < m_display_start)
        {
          --m_display_start;
        }
      }
    }
    if(IsKeyPressed(KEY_UP) == true)
    {
      long m_focus_y_temp{max(m_focus_y - 1, static_cast<long>(0))};
      if(m_focus_x + m_focus_y_temp * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_y = max(m_focus_y - 1, static_cast<long>(0));
        if(m_focus_y < m_display_start)
        {
          --m_display_start;
        }
      }
    }
  
    if(IsKeyPressed(KEY_DOWN) == true)
    {
      long m_focus_y_temp{min(m_focus_y + 1, m_max_rows - 1)};
      if(m_focus_x + m_focus_y_temp * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_y = min(m_focus_y + 1, m_max_rows - 1);
        if(m_focus_y > m_display_start + m_display_rows - 1)
        {
          ++m_display_start;
        }
      }
    }
  
    if(IsKeyPressed(KEY_LEFT) == true)
    {
      long m_focus_x_temp{max(m_focus_x - 1, static_cast<long>(0))};
      if(m_focus_x_temp + m_focus_y * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_x = max(m_focus_x - 1, static_cast<long>(0));
      }
    }

    if(IsKeyPressed(KEY_RIGHT) == true)
    {
      long m_focus_x_temp{min(m_focus_x + 1, m_columns - 1)};
      if(m_focus_x_temp + m_focus_y * m_columns < static_cast<long>(m_choices.size()))
      {
        m_focus_x = min(m_focus_x + 1, m_columns - 1);
      }
    }

    if(IsKeyPressed(KEY_Z) == true)
    {
      on_click();
    }
    cursor->set_destination(m_x + m_spacing_x * m_focus_x, m_y + m_spacing_y * (m_focus_y - m_display_start));
    m_highlighted_item = m_focus_x + m_focus_y * m_columns;
  }
}

template <>
void Selection<string>::render(const vector<Fnt*> & fonts, World* world, const string & party_member_name) const
{
  if(m_show_menu == true)
  {
    long display_start{m_display_start};
    long display_end{m_display_start + m_display_rows};
    long x{m_x};
    long y{m_y};
    long item_index{display_start * m_columns};

    for(long i{display_start}; i < display_end; ++i)
    {
      for(long j{0}; j < m_columns; ++j)
      {
        if(m_render_mode == "Normal")
        {
          render_item(x, y, item_index, fonts[0]);
        }
        else if(m_render_mode == "Items")
        {
          world->render_item(x, y, fonts[0], item_index, m_spacing_x);
        }
        else if(m_render_mode == "Key Items")
        {
          world->render_key_item(x, y, fonts[0], item_index);
        }
        else if(m_render_mode == "Stats")
        {
          render_item(x, y, item_index, fonts[0]);
          world->render_stat(x, y, fonts[0], item_index, m_spacing_x, party_member_name);
        }
        x += m_spacing_x;
        ++item_index;
      }
      y += m_spacing_y;
      x = m_x;
    }
  }
}

template <>
string Selection<string>::c_get_options() const
{
  string menu_items{""};
  for(long i{0}; i < static_cast<long>(m_choices.size()); ++i)
  {
    menu_items += *m_choices[i];
    if(i != static_cast<long>(m_choices.size()) - 1)
    {
      menu_items += ", ";
    }
  }
  return menu_items;
}

template <>
void Selection<string>::on_click()
{
  m_selected_item = m_focus_x + m_focus_y * m_columns;
}

template <>
void Selection<Player_Summary>::on_click()
{
  m_selected_item = m_focus_x + m_focus_y * m_columns;
}