/********************************************************************
	created:	2010/06/02
	created:	6:2:2010   13:20
	file base:	FairyBulletSwayOperator
	file ext:	h
	author:		�¾���
	email:		pizi0475@163.com
	purpose:	
*********************************************************************/
#ifndef FairyBulletSwayOperator_h__
#define FairyBulletSwayOperator_h__

#include "FairyBulletOperator.h"
#include "Core/FairyPrerequisites.h"
#include "OgreVector3.h"

namespace Fairy
{
	class BulletEventSystem;
	class BulletSwayOperator : public BulletOperator
	{
	public:
		BulletSwayOperator(BulletEventSystem* eventSystem);
		virtual ~BulletSwayOperator();

		virtual void operateBulletEventSystem(Real timeElapsed);

		virtual void copyParameters(BulletOperator& newOperator) const;

		class CmdAmplitude : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* source) const;
			void doSet(void* target, const String& val);
		};

		class CmdFrequency : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* source) const;
			void doSet(void* target, const String& val);
		};

		const Fairy::Real&			getAmplitude() const { return m_amplitude; }
		void						setAmplitude(const Fairy::Real& val) {m_amplitude = val;}

		const Fairy::Real&			getFrequency() const { return m_frequency; }
		void						setFrequency(const Fairy::Real& val) {m_frequency = val;}

		static CmdAmplitude		ms_amplitudeCmd;
		static CmdFrequency		ms_frequencyCmd;

	protected:

		/// ���
		Real	m_amplitude;
		/// Ƶ��
		Real	m_frequency;

	private:
	};
}
#endif // FairyBulletSwayOperator_h__