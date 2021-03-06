/*ckwg +5
 * Copyright 2010 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef vidtk_property_map_h_
#define vidtk_property_map_h_

/**\file
   \brief
  Method and field definition of a property map.
*/
#include <boost/any.hpp>
#include <vcl_stdexcept.h>
#include <vcl_string.h>
#include <vcl_map.h>
#include <utilities/checked_bool.h>

namespace
{
  typedef vcl_map< vcl_string, unsigned >  key_map_type;
}

namespace vidtk
{

///Method and field definitions of a property map.
class property_map
{
public:
  ///Creates name for type unsigned.
  typedef unsigned key_type;

  ///Return true is the key is found; otherwise false.
  template<class T>
  checked_bool get( key_type const& key, T& val ) const
  {
    map_type::const_iterator it = map_.find( key );
    if( it == map_.end() )
    {
      return "key not found";
    }
    else
    {
      val = boost::any_cast<T>( it->second );
      return true;
    }
  }

  /// \brief Return a const pointer to the object in the map.
  ///
  /// Will return NULL if the key is not found.
  template<class T>
  T const* get_if_avail( key_type const& key ) const
  {
    map_type::const_iterator it = map_.find( key );
    if( it == map_.end() )
    {
      return 0;
    }
    else
    {
      return &boost::any_cast<T const&>( it->second );
    }
  }

  /// \brief Return a pointer to the object in the map.
  ///
  /// Will return NULL if the key is not found.
  template<class T>
  T* get_if_avail( key_type const& key )
  {
    map_type::iterator it = map_.find( key );
    if( it == map_.end() )
    {
      return 0;
    }
    else
    {
      return &boost::any_cast<T&>( it->second );
    }
  }

  /// \brief Return a const pointer to the object in the map.
  ///
  /// Will return NULL if the key is not found.
  template<class T>
  void get_if_avail( key_type const& key, T const* val ) const
  {
    val = get_if_avail<T>( key );
  }

  /// \brief Return a pointer to the object in the map.
  ///
  /// Will return NULL if the key is not found.
  template<class T>
  void get_if_avail( key_type const& key, T* val )
  {
    val = get_if_avail<T>( key );
  }

  ///Return the reference if one exists; otherwise create the reference.
  template<class T>
  T& get_or_create_ref( key_type const& key )
  {
    map_type::iterator it = map_.find( key );
    if( it == map_.end() )
    {
      it = map_.insert( map_type::value_type( key, T() ) ).first;
    }
    return boost::any_cast<T&>( it->second );
  }

  ///Returns true if the map has a given key; otherwise returns false.
  bool has( key_type const& key ) const
  {
    map_type::const_iterator it = map_.find( key );
    return it != map_.end();
  }


  /// \brief Check if a key is set to \c true.
  ///
  /// This function is a shortcut for boolean-valued properties, and
  /// returns \c true if and only if the property exists in the map
  /// and the value is \c true.
  bool is_set( key_type const& key ) const
  {
    map_type::const_iterator it = map_.find( key );
    if( it == map_.end() )
    {
      return false;
    }
    else
    {
      return boost::any_cast<bool>( it->second );
    }
  }

  ///Set the value of the given key to the given value.
  template<class T>
  void set( key_type const& key, T const& val )
  {
    map_[key] = val;
  }
  ///Sets the key value.
  template<class T>
  void set( vcl_string const& key_str, T const& val )
  {
    this->set( key(key_str), val );
  }
  ///Return the value of the given key.
  template<class T>
  checked_bool get( vcl_string const& key_str, T& val ) const
  {
    return this->get( key(key_str), val );
  }
  ///Return the key value if it is available as a constant.
  template<class T>
  T const* get_if_avail( vcl_string const& key_str ) const
  {
    return get_if_avail<T>( key(key_str) );
  }
  ///Return the key value is available
  template<class T>
  T* get_if_avail( vcl_string const& key_str )
  {
    return get_if_avail<T>( key(key_str) );
  }
  ///Return the key value is available
  template<class T>
  void get_if_avail( vcl_string const& key_str, T const* val ) const
  {
    val = get_if_avail<T>( key_str );
  }
  ///Return the key value is available
  template<class T>
  void get_if_avail( vcl_string const& key_str, T* val )
  {
    val = get_if_avail<T>( key_str );
  }

  ///Returns the value of the reference. If the reference doesn't exist, it creates one and returns that value.
  template<class T>
  T& get_or_create_ref( vcl_string const& key_str )
  {
    return this->get_or_create_ref<T>( key(key_str) );
  }
  ///Returns true is the key exists; otherwise false;
  bool has( vcl_string const& key_str ) const
  {
    return this->has( key(key_str) );
  }
  ///Returns true if the key is set to the given key; otherwise false.
  bool is_set( vcl_string const& key_str ) const
  {
    return this->is_set( key(key_str) );
  }

  ///Returns true is there are no properties stored in this map; otherwise returns false.
  bool empty() const
  {
    return map_.empty();
  }

  /// The number of the the properties stored in the map.
  unsigned size() const
  {
    return map_.size();
  }
  ///Returns the map of keys to values
  static key_map_type key_map();


  /// \brief Return a key from a name.
  ///
  /// For a given run of the program, a given name will return the
  /// same key.  However, the mapping is not guaranteed to be constant
  /// across different runs of the program.
  static key_type key( vcl_string const& name );

private:
  typedef vcl_map< key_type, boost::any > map_type;

  map_type map_;
};


} // end namespace vidtk


#endif // vidtk_property_map_h_
