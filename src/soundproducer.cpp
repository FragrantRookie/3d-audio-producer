#include "soundproducer.h"

SoundProducer::SoundProducer()
{
	m_buffer = 0;
	m_source = 0;
	
	producer_position_vector.resize(3);
	producer_position_vector[POSITION_INDEX::X] = 0;
	producer_position_vector[POSITION_INDEX::Y] = 0;
	producer_position_vector[POSITION_INDEX::Z] = 0;
	

}

SoundProducer::~SoundProducer()
{
	if(m_source != 0)
	{
		alDeleteSources(1, &m_source);
	}
	
	if(m_buffer != 0)
	{
		alDeleteBuffers(1, &m_buffer);
	}
}

void SoundProducer::InitSoundProducer(std::string& thisName,double& x, double& y, double& z)
{
	name = thisName;
	
	//set position
	producer_position_vector[POSITION_INDEX::X] = x;
	producer_position_vector[POSITION_INDEX::Y] = y;
	producer_position_vector[POSITION_INDEX::Z] = z; 
	
	//make box
	//create ShapeDrawable object
	m_renderObject = new osg::ShapeDrawable;
	m_box = new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f),1.0f);
	
	//make ShapeDrawable object a box 
	//initialize box at certain position 
	m_renderObject->setShape(m_box);
	//set color of ShapeDrawable object with box
	m_renderObject->setColor( osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f) );
	
	m_geode = new osg::Geode;
	m_geode->addDrawable( m_renderObject.get() );
	
	
	// Create transformation node
	m_paTransform = new osg::PositionAttitudeTransform;
	
	//initialize transform and add geode to it
	m_paTransform->setPosition( osg::Vec3(x,y,z));
	m_paTransform->addChild(m_geode);
}

void SoundProducer::SetNameString(std::string& thisName){ name = thisName;}
std::string SoundProducer::GetNameString(){ return name;}

void SoundProducer::setPositionX(double& x)
{		
	producer_position_vector[POSITION_INDEX::X] = x;
	
	m_paTransform->setPosition(osg::Vec3(x, 
								producer_position_vector[POSITION_INDEX::Y], 
								producer_position_vector[POSITION_INDEX::Z]));
	
} 

float SoundProducer::getPositionX(){return producer_position_vector[POSITION_INDEX::X];} 

void SoundProducer::setPositionY(double& y)
{
	producer_position_vector[POSITION_INDEX::Y] = y;
	
	m_paTransform->setPosition(osg::Vec3(producer_position_vector[POSITION_INDEX::X], 
								y, 
								producer_position_vector[POSITION_INDEX::Z]));
} 

float SoundProducer::getPositionY(){return producer_position_vector[POSITION_INDEX::Y];}

void SoundProducer::setPositionZ(double& z)
{
	producer_position_vector[POSITION_INDEX::Z] = z;
	
	m_paTransform->setPosition(osg::Vec3(producer_position_vector[POSITION_INDEX::X], 
								producer_position_vector[POSITION_INDEX::Y], 
								z));
} 
float SoundProducer::getPositionZ(){return producer_position_vector[POSITION_INDEX::Z];}

void SoundProducer::setFilepathToSound(std::string& filepath){m_filepath = filepath;}

std::string& SoundProducer::getFilepathToSound(){return m_filepath;}

ALuint* SoundProducer::getBuffer(){return &m_buffer;}

ALuint* SoundProducer::getSource(){return &m_source;}

osg::ShapeDrawable* SoundProducer::getRenderObject(){return m_renderObject;}

osg::Geode* SoundProducer::getGeodeNode(){return m_geode;}

osg::PositionAttitudeTransform* SoundProducer::getTransformNode(){return m_paTransform;}
