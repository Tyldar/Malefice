#include "SceneMesh.h"

#include <iostream>

namespace ecs
{

	SceneMesh::SceneMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable, const std::string& namePK3): AScene(device, newNameTexture, newNameMesh, newPickableFlags, isCollisionable),
		m_node(nullptr)
	{
		irr::scene::IAnimatedMesh*		mesh;
		
		if (namePK3 != "")
		{
			m_device->getFileSystem()->addFileArchive((MEDIA_PATH + namePK3).c_str());
			mesh = m_smgr->getMesh(newNameMesh.c_str());
		}
		else
		{
			//TODO: constructor without decompression
		}
		if (mesh)
			m_node = m_smgr->addOctreeSceneNode(mesh->getMesh(0), 0, newPickableFlags);
		else
			std::cerr << "Error constructor SceneMesh : mesh NULL !!" << std::endl;

		if (m_node)
			m_node->setTriangleSelector(m_smgr->createOctreeTriangleSelector(m_node->getMesh(), m_node, 128));
		else
			std::cerr << "Error constructor SceneMesh : m_node NULL !!" << std::endl;

		if (IS_COLLISIONABLE)
		{
			m_selector = m_smgr->createOctreeTriangleSelector(m_node->getMesh(), m_node, 128);
			m_node->setTriangleSelector(m_selector);
			irr::scene::ISceneNodeAnimator*	animator = m_smgr->createCollisionResponseAnimator(m_selector,
				m_smgr->getActiveCamera(),
				irr::core::vector3df(30.f, 50.f, 30.f),
				irr::core::vector3df(0.f, -10.f, 0.f),
				irr::core::vector3df(0.f, 30.f, 0.f));
			m_smgr->getActiveCamera()->addAnimator(animator);
			animator->drop();
		}
	}

	SceneMesh::~SceneMesh()
	{
	}


	void SceneMesh::setPosition(const Position& newPosition)
	{
		m_node->setPosition(newPosition.getVectorPosition());
		m_node->setRotation(newPosition.getVectorRotation());
	}


	void	SceneMesh::dump(std::ostream& os)	const
	{
		os << "SceneMesh {}";
	}
}