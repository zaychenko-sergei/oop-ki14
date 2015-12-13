// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

#include <sstream>

/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_1_parent_node_as_root )
{
	Controller c;
	c.startParentNode( "1. ROOT" );
	c.endParentNode();

	NodePath nodePath( 1 );
	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == true );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. ROOT" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_2_parent_node_with_empty_description )
{
	Controller c;

	ASSERT_THROWS(
			c.startParentNode( "" );
		,	Messages::EmptyDescriptionText
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_3_parent_node_make_invisible )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.makeInvisible( nodePath );

	assert( c.isVisible( nodePath ) == false );
	assert( c.isExpanded( nodePath ) == true );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_4_parent_node_make_visible )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.makeInvisible( nodePath );
	c.makeVisible( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == true );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_5_parent_node_make_invisible_already_invisible )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.makeInvisible( nodePath );
	c.makeInvisible( nodePath );
	c.makeInvisible( nodePath );
	c.makeInvisible( nodePath );

	assert( c.isVisible( nodePath ) == false );
	assert( c.isExpanded( nodePath ) == true );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_6_parent_node_make_visible_already_visible )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.makeVisible( nodePath );
	c.makeVisible( nodePath );
	c.makeVisible( nodePath );
	c.makeVisible( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == true );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_7_parent_node_collapse )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.collapse( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_8_parent_node_make_expand )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.collapse( nodePath );
	c.expand( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == true );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_9_parent_node_collapse_already_collapsed )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.collapse( nodePath );
	c.collapse( nodePath );
	c.collapse( nodePath );
	c.collapse( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_10_parent_node_make_expand_already_expanded )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath( 1 );
	c.expand( nodePath );
	c.expand( nodePath );
	c.expand( nodePath );
	c.expand( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == true );
	assert( c.isLeaf( nodePath ) == false );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_1_11_parent_node_several_root_nodes )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();
	c.startParentNode( "2. TOP" );
	c.endParentNode();

	NodePath nodePath1( 1 );
	assert( c.isVisible( nodePath1 ) == true );
	assert( c.isExpanded( nodePath1 ) == true );
	assert( c.isLeaf( nodePath1 ) == false );
	assert( c.getNodeDescription( nodePath1 ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath1 ) == 0 );

	NodePath nodePath2( 2 );
	assert( c.isVisible( nodePath2 ) == true );
	assert( c.isExpanded( nodePath2 ) == true );
	assert( c.isLeaf( nodePath2 ) == false );
	assert( c.getNodeDescription( nodePath2 ) == "2. TOP" );
	assert( c.getNodeChildrenCount( nodePath2 ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_1_leaf_node_as_root )
{
	Controller c;
	c.addLeafNode( "1. ROOT" );

	NodePath nodePath( 1 );
	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. ROOT" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_2_leaf_node_with_empty_description )
{
	Controller c;

	ASSERT_THROWS(
			c.addLeafNode( "" );
		,	Messages::EmptyDescriptionText
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_3_leaf_node_make_invisible )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.makeInvisible( nodePath );

	assert( c.isVisible( nodePath ) == false );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_4_leaf_node_make_visible )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.makeInvisible( nodePath );
	c.makeVisible( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_5_leaf_node_make_invisible_already_visible )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.makeInvisible( nodePath );
	c.makeInvisible( nodePath );
	c.makeInvisible( nodePath );
	c.makeInvisible( nodePath );

	assert( c.isVisible( nodePath ) == false );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_6_leaf_node_make_visible_already_visible )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.makeVisible( nodePath );
	c.makeVisible( nodePath );
	c.makeVisible( nodePath );
	c.makeVisible( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_7_leaf_node_collapse )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.collapse( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_8_leaf_node_make_expand )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.collapse( nodePath );
	c.expand( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_9_leaf_node_collapse_already_collapsed )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.collapse( nodePath );
	c.collapse( nodePath );
	c.collapse( nodePath );
	c.collapse( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_10_leaf_node_make_expand_already_expanded )
{
	Controller c;
	c.addLeafNode( "1. TOP" );

	NodePath nodePath( 1 );
	c.expand( nodePath );
	c.expand( nodePath );
	c.expand( nodePath );
	c.expand( nodePath );

	assert( c.isVisible( nodePath ) == true );
	assert( c.isExpanded( nodePath ) == false );
	assert( c.isLeaf( nodePath ) == true );
	assert( c.getNodeDescription( nodePath ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_2_11_leaf_node_several_root_nodes )
{
	Controller c;
	c.addLeafNode( "1. TOP" );
	c.addLeafNode( "2. TOP" );

	NodePath nodePath1( 1 );
	assert( c.isVisible( nodePath1 ) == true );
	assert( c.isExpanded( nodePath1 ) == false );
	assert( c.isLeaf( nodePath1 ) == true );
	assert( c.getNodeDescription( nodePath1 ) == "1. TOP" );
	assert( c.getNodeChildrenCount( nodePath1 ) == 0 );

	NodePath nodePath2( 2 );
	assert( c.isVisible( nodePath2 ) == true );
	assert( c.isExpanded( nodePath2 ) == false );
	assert( c.isLeaf( nodePath2 ) == true );
	assert( c.getNodeDescription( nodePath2 ) == "2. TOP" );
	assert( c.getNodeChildrenCount( nodePath2 ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_3_cannot_resolve_path_with_invalid_root_node )
{
	Controller c;
	c.startParentNode( "1. TOP" );
	c.endParentNode();

	NodePath nodePath1( 0 );
	ASSERT_THROWS(
			c.expand( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath1 );
		,	Messages::NodePathUnresolved
	);

	NodePath nodePath2( 2 );
	ASSERT_THROWS(
			c.expand( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath2 );
		,	Messages::NodePathUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_4_cannot_resolve_path_with_invalid_middle_node )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath1( 1 );
	nodePath1.pushIndex( 1 ).pushIndex( 0 ).pushIndex( 1 );
	ASSERT_THROWS(
			c.expand( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath1 );
		,	Messages::NodePathUnresolved
	);
	
	NodePath nodePath2( 1 );
	nodePath2.pushIndex( 1 ).pushIndex( 2 ).pushIndex( 1 );
	ASSERT_THROWS(
			c.expand( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath2 );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath2 );
		,	Messages::NodePathUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_5_cannot_resolve_path_with_excess_items_at_the_leaf_end )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
				c.endParentNode();
			c.endParentNode();
			c.addLeafNode( "1.2 ANOTHER");
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 ).pushIndex( 2 ).pushIndex( 1 );
	ASSERT_THROWS(
			c.expand( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath );
		,	Messages::NodePathUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_6_cannot_resolve_path_with_excess_items_at_the_parent_end )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 ).pushIndex( 1 ).pushIndex( 1 ).pushIndex( 1 );
	ASSERT_THROWS(
			c.expand( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath );
		,	Messages::NodePathUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_7_cannot_resolve_path_with_2_items_and_root_leaf )
{
	Controller c;
	c.addLeafNode( "1. LEAF" );

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 );
	ASSERT_THROWS(
			c.expand( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath );
		,	Messages::NodePathUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_8_cannot_resolve_path_with_collapsed_items_on_the_way )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 ).pushIndex( 1 );
	c.collapse( nodePath );

	nodePath.pushIndex( 1 );
	ASSERT_THROWS(
			c.expand( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.collapse( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeInvisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.makeVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isVisible( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isExpanded( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.isLeaf( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeDescription( nodePath );
		,	Messages::NodePathUnresolved
	);
	ASSERT_THROWS(
			c.getNodeChildrenCount( nodePath );
		,	Messages::NodePathUnresolved
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_9_cannot_resolve_path_with_invisible_items_on_the_way )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 ).pushIndex( 1 );
	c.makeInvisible( nodePath );

	nodePath.pushIndex( 1 );
	assert( c.getNodeDescription( nodePath ) == "1.1.1.1 LOW" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_10_1_build_invalid_tree_only_end_item_at_root )
{
	Controller c;

	ASSERT_THROWS(
			c.endParentNode();
		,	Messages::DidNotOpenParentPreviously
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_10_2_build_invalid_tree_twice_end_item_in_tree )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	ASSERT_THROWS(
			c.endParentNode();
		,	Messages::DidNotOpenParentPreviously
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_1_show_simple_tree )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
					c.addLeafNode( "1.1.1.1.1 LEAF");
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result ==	"1. TOP\n"
						"\t1.1 MIDDLE1\n"
						"\t\t1.1.1 MIDDLE2\n"
						"\t\t\t1.1.1.1 LOW\n"
						"\t\t\t\t1.1.1.1.1 LEAF\n"
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_2_show_empty_tree )
{
	Controller c;

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result == "" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_3_show_root_invisible_parent_node )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
					c.addLeafNode( "1.1.1.1.1 LEAF");
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	c.makeInvisible( nodePath );

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result ==	"" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_4_show_root_invisible_leaf_node )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
					c.addLeafNode( "1.1.1.1.1 LEAF");
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 ).pushIndex( 1 ).pushIndex( 1 ).pushIndex( 1 );
	c.makeInvisible( nodePath );

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result ==	"1. TOP\n"
						"\t1.1 MIDDLE1\n"
						"\t\t1.1.1 MIDDLE2\n"
						"\t\t\t1.1.1.1 LOW\n"
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_5_show_root_collapsed_parent_node )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
					c.addLeafNode( "1.1.1.1.1 LEAF");
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	c.collapse( nodePath );

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result == "1. TOP\n" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_6_show_invisible_branch )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
					c.addLeafNode( "1.1.1.1.1 LEAF");
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 );
	c.makeInvisible( nodePath );

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result == "1. TOP\n" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_7_show_collapsed_branch )
{
	Controller c;
	c.startParentNode( "1. TOP" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.startParentNode( "1.1.1.1 LOW" );
					c.addLeafNode( "1.1.1.1.1 LEAF");
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	NodePath nodePath( 1 );
	nodePath.pushIndex( 1 );
	c.collapse( nodePath );

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result ==	"1. TOP\n"
						"\t1.1 MIDDLE1\n"
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_1_11_8_show_large_tree )
{
	Controller c;
	c.startParentNode( "1. TOP1" );
		c.startParentNode( "1.1 MIDDLE1" );
			c.startParentNode( "1.1.1 MIDDLE2" );
				c.addLeafNode( "1.1.1.1 GRAND");
				c.startParentNode( "1.1.1.2 LOW" );
					c.addLeafNode( "1.1.1.2.1 LEAF1");
					c.addLeafNode( "1.1.1.2.2 LEAF2");
				c.endParentNode();
			c.endParentNode();
			c.addLeafNode( "1.1.2 NODE1");
			c.addLeafNode( "1.1.3 NODE2");
		c.endParentNode();
	c.endParentNode();
	c.addLeafNode( "2. TOP2");
	c.startParentNode( "3. TOP3" );
		c.addLeafNode( "3.1 NODE1");
		c.addLeafNode( "3.2 NODE2");
		c.startParentNode( "3.3 MIDDLE1" );
			c.startParentNode( "3.3.1 ZERO" );
				c.addLeafNode( "3.3.1.1 SWAG");
				c.startParentNode( "3.3.1.2 LOW" );
					c.addLeafNode( "3.3.1.2.1 LEAF1");
				c.endParentNode();
			c.endParentNode();
		c.endParentNode();
	c.endParentNode();

	std::stringstream s;
	c.show( s );
	std::string result = s.str();

	assert( result ==	"1. TOP1\n"
						"\t1.1 MIDDLE1\n"
						"\t\t1.1.1 MIDDLE2\n"
						"\t\t\t1.1.1.1 GRAND\n"
						"\t\t\t1.1.1.2 LOW\n"
						"\t\t\t\t1.1.1.2.1 LEAF1\n"
						"\t\t\t\t1.1.1.2.2 LEAF2\n"
						"\t\t1.1.2 NODE1\n"
						"\t\t1.1.3 NODE2\n"
						"2. TOP2\n"
						"3. TOP3\n"
						"\t3.1 NODE1\n"
						"\t3.2 NODE2\n"
						"\t3.3 MIDDLE1\n"
						"\t\t3.3.1 ZERO\n"
						"\t\t\t3.3.1.1 SWAG\n"
						"\t\t\t3.3.1.2 LOW\n"
						"\t\t\t\t3.3.1.2.1 LEAF1\n"
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( trees_2_1_complex_cases_simple_flow )
{
	Controller c;

	c.startParentNode( "1. AAA" );
		c.startParentNode( "1.1 BB" );
			c.addLeafNode( "1.1.1 C" );
			c.addLeafNode( "1.1.2 D" );
		c.endParentNode();
		c.startParentNode( "1.2 EE" );
			c.addLeafNode( "1.2.1 F" );
		c.endParentNode();
		c.addLeafNode( "1.3 GG" );
	c.endParentNode();

	std::stringstream o;
	c.show( o );

	assert( o.str() ==	"1. AAA\n"
						"\t1.1 BB\n"
						"\t\t1.1.1 C\n"
						"\t\t1.1.2 D\n"
						"\t1.2 EE\n"
						"\t\t1.2.1 F\n"
						"\t1.3 GG\n" );

	assert( !c.isLeaf( NodePath( 1 ).pushIndex( 1 ) ) );
	assert( c.isLeaf( NodePath( 1 ).pushIndex( 3 ) ) );

	assert( c.isVisible( NodePath( 1 ).pushIndex( 1 ) ) );
	c.makeInvisible( NodePath( 1 ).pushIndex( 1 ) );
	assert( !c.isVisible( NodePath( 1 ).pushIndex( 1 ) ) );

	o.str( "" );
	o.clear();
	c.show( o );

	assert( o.str() ==	"1. AAA\n"
						"\t1.2 EE\n"
						"\t\t1.2.1 F\n"
						"\t1.3 GG\n" );

	c.makeVisible( NodePath( 1 ).pushIndex( 1 ) );
	c.collapse( NodePath( 1 ).pushIndex( 2 ) );

	o.str( "" );
	o.clear();
	c.show( o );

	assert( o.str() ==	"1. AAA\n"
						"\t1.1 BB\n"
						"\t\t1.1.1 C\n"
						"\t\t1.1.2 D\n"
						"\t1.2 EE\n"
						"\t1.3 GG\n" );

	assert( c.isExpanded( NodePath( 1 ).pushIndex( 1 ) ) );
	assert( !c.isExpanded( NodePath( 1 ).pushIndex( 2 ) ) );
}


/*****************************************************************************/
