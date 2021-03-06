// Copyright (c) 2003-2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.2-branch/Curved_kernel/include/CGAL/Circular_arc_2.h $
// $Id: Circular_arc_2.h 29284 2006-03-09 13:36:00Z teillaud $
//
// Author(s)     : Monique Teillaud, Sylvain Pion


// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_CIRCULAR_ARC_2_H
#define CGAL_CIRCULAR_ARC_2_H

namespace CGAL {
  
template <class CircularKernel> 
class Circular_arc_2 
  : public CircularKernel::Kernel_base::Circular_arc_2
{
  typedef typename CircularKernel::RT             RT;
  typedef typename CircularKernel::FT             FT;
  typedef typename CircularKernel::Point_2        Point_2;
  typedef typename CircularKernel::Line_2         Line_2;
  typedef typename CircularKernel::Circle_2       Circle_2;
  typedef typename CircularKernel::Circular_arc_point_2
                                                Circular_arc_point_2;
  
  typedef typename CircularKernel::Kernel_base::Circular_arc_2 RCircular_arc_2; 
  // RCircular_arc_2 to avoid clash with self 
public:
  typedef  RCircular_arc_2 Rep;
  typedef  CircularKernel   R; 
  

  const Rep& rep() const
  {
    return *this;
  }

  Rep& rep()
  {
    return *this;
  }


  Circular_arc_2()
    : RCircular_arc_2(typename R::Construct_circular_arc_2()())
  {}

  Circular_arc_2(const Circle_2 &c)
    : RCircular_arc_2(typename R::Construct_circular_arc_2()(c))
  {}

  Circular_arc_2(const Circle_2 &support, 
                 const Line_2 &l1, const bool b_l1,
                 const Line_2 &l2, const bool b_l2)
    : RCircular_arc_2(typename 
		      R::Construct_circular_arc_2()(support,l1,b_l1,l2,b_l2))
  {}

  Circular_arc_2(const Circle_2 &c, 
		 const Circle_2 &c1, const bool b_1,
		 const Circle_2 &c2, const bool b_2)
    : RCircular_arc_2(typename 
		      R::Construct_circular_arc_2()(c,c1,b_1,c2,b_2))
  {}

  Circular_arc_2(const Circular_arc_2 &A, const bool b,
		 const Circle_2 &ccut, const bool b_cut)
    : RCircular_arc_2(typename 
		      R::Construct_circular_arc_2()(A, b, ccut, b_cut))
    {}

  Circular_arc_2(const Point_2 &start,
                 const Point_2 &middle,
                 const Point_2 &end)
    : RCircular_arc_2(typename 
		      R::Construct_circular_arc_2()(start, middle, end)) 
  {}
  
  Circular_arc_2(const Circle_2 &support,
                 const Circular_arc_point_2 &begin,
                 const Circular_arc_point_2 &end)
    : RCircular_arc_2(typename 
		      R::Construct_circular_arc_2()(support, begin, end)) 
  {}
 
  Circular_arc_2(const Point_2 &start,
                 const Point_2 &end,
		 const FT &bulge)
    : RCircular_arc_2(typename 
		      R::Construct_circular_arc_2()(start, end, bulge)) 
  {}
  
 Circular_arc_2(const RCircular_arc_2 & a)
    : RCircular_arc_2(a)
  {}


  typename Qualified_result_of    
  <typename R::Construct_circular_source_vertex_2,Circular_arc_2>::type
  //const Circular_arc_point_2 &
  source() const
  {
    return typename R::Construct_circular_source_vertex_2()(*this);
  }

  typename Qualified_result_of
  <typename R::Construct_circular_target_vertex_2,Circular_arc_2>::type
  //const Circular_arc_point_2 &
  target() const
  {
    return typename R::Construct_circular_target_vertex_2()(*this);
  }

  typename Qualified_result_of
  <typename R::Construct_circular_min_vertex_2,Circular_arc_2>::type
  //const Circular_arc_point_2 & 
  left() const
  {
    return typename R::Construct_circular_min_vertex_2()(*this);
  }

  typename Qualified_result_of
  <typename R::Construct_circular_max_vertex_2,Circular_arc_2>::type
  //const Circular_arc_point_2 & 
  right() const
  {
    return typename R::Construct_circular_max_vertex_2()(*this);
  }

  bool is_x_monotone() const
  {
    return typename R::Is_x_monotone_2()(*this);
  }

  bool is_y_monotone() const
  {
    return typename R::Is_y_monotone_2()(*this);
  }

  bool on_upper_part() const
  {
    return typename R::On_upper_part_2()(*this);
  }

  typename Qualified_result_of
  <typename R::Construct_supporting_circle_2,Circular_arc_2>::type
  //const Circle_2 &
  supporting_circle() const
  {
    return typename R::Construct_supporting_circle_2()(*this);
  }

  const Point_2 & center() const
  {
    return typename R::Construct_supporting_circle_2()(*this).center();
  }

  const FT & squared_radius() const
  {
    return typename R::Construct_supporting_circle_2()(*this).squared_radius();
  }

 Bbox_2 bbox(void) const
 {
   return typename R::Construct_bbox_2()(*this);
 }

};

  template < typename CK >
  std::ostream &
  operator<<(std::ostream & os, const Circular_arc_2<CK> &a)
  {
    // The output format is :
    // - supporting circle
    // - circle c1
    // - bool b1
    // - circle c2
    // - bool b2
    return os << a.supporting_circle() << " "
	      << a.source() << " "
	      << a.target() << " ";
  }
  
  template < typename CK >
  std::istream &
  operator>>(std::istream & is, Circular_arc_2<CK> &a)
  {
    typename CK::Circle_2 s;
    typename CK::Circular_arc_point_2 p1;
    typename CK::Circular_arc_point_2 p2;
    is >> s >> p1 >> p2 ;
    if (is)
      a = Circular_arc_2<CK>(s, p1, p2);
    return is;
  }

} // namespace CGAL

#endif // CGAL_CIRCULAR_ARC_2_H
