#	cd $BOX2DPATH/Build
#	cmake -DBOX2D_INSTALL=ON -DBOX2D_BUILD_SHARED=ON ..
#	make
#	make install

mkdir /usr/include/Box2D/
mkdir /usr/include/Box2D/Collision
mkdir /usr/include/Box2D/Collision/Shapes
mkdir /usr/include/Box2D/Common
mkdir /usr/include/Box2D/Dynamics
mkdir /usr/include/Box2D/Dynamics/Contacts
mkdir /usr/include/Box2D/Dynamics/Joints
mkdir /usr/lib/Box2D/
cp /usr/local/include/Box2D/Box2D.h                                                /usr/include/Box2D.h                                                
cp /usr/local/include/Box2D/Collision/b2BroadPhase.h                               /usr/include/Box2D/Collision/b2BroadPhase.h
cp /usr/local/include/Box2D/Collision/b2Collision.h                                /usr/include/Box2D/Collision/b2Collision.h
cp /usr/local/include/Box2D/Collision/b2Distance.h                                 /usr/include/Box2D/Collision/b2Distance.h
cp /usr/local/include/Box2D/Collision/b2DynamicTree.h                              /usr/include/Box2D/Collision/b2DynamicTree.h
cp /usr/local/include/Box2D/Collision/b2TimeOfImpact.h                             /usr/include/Box2D/Collision/b2TimeOfImpact.h
cp /usr/local/include/Box2D/Collision/Shapes/b2CircleShape.h                       /usr/include/Box2D/Collision/Shapes/b2CircleShape.h
cp /usr/local/include/Box2D/Collision/Shapes/b2PolygonShape.h                      /usr/include/Box2D/Collision/Shapes/b2PolygonShape.h
cp /usr/local/include/Box2D/Collision/Shapes/b2Shape.h                             /usr/include/Box2D/Collision/Shapes/b2Shape.h
cp /usr/local/include/Box2D/Common/b2BlockAllocator.h                              /usr/include/Box2D/Common/b2BlockAllocator.h
cp /usr/local/include/Box2D/Common/b2Math.h                                        /usr/include/Box2D/Common/b2Math.h
cp /usr/local/include/Box2D/Common/b2Settings.h                                    /usr/include/Box2D/Common/b2Settings.h
cp /usr/local/include/Box2D/Common/b2StackAllocator.h                              /usr/include/Box2D/Common/b2StackAllocator.h
cp /usr/local/include/Box2D/Dynamics/b2Body.h                                      /usr/include/Box2D/Dynamics/b2Body.h
cp /usr/local/include/Box2D/Dynamics/b2ContactManager.h                            /usr/include/Box2D/Dynamics/b2ContactManager.h
cp /usr/local/include/Box2D/Dynamics/b2Fixture.h                                   /usr/include/Box2D/Dynamics/b2Fixture.h
cp /usr/local/include/Box2D/Dynamics/b2Island.h                                    /usr/include/Box2D/Dynamics/b2Island.h
cp /usr/local/include/Box2D/Dynamics/b2TimeStep.h                                  /usr/include/Box2D/Dynamics/b2TimeStep.h
cp /usr/local/include/Box2D/Dynamics/b2World.h                                     /usr/include/Box2D/Dynamics/b2World.h
cp /usr/local/include/Box2D/Dynamics/b2WorldCallbacks.h                            /usr/include/Box2D/Dynamics/b2WorldCallbacks.h
cp /usr/local/include/Box2D/Dynamics/Contacts/b2CircleContact.h                    /usr/include/Box2D/Dynamics/Contacts/b2CircleContact.h
cp /usr/local/include/Box2D/Dynamics/Contacts/b2Contact.h                          /usr/include/Box2D/Dynamics/Contacts/b2Contact.h
cp /usr/local/include/Box2D/Dynamics/Contacts/b2ContactSolver.h                    /usr/include/Box2D/Dynamics/Contacts/b2ContactSolver.h
cp /usr/local/include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h          /usr/include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h
cp /usr/local/include/Box2D/Dynamics/Contacts/b2PolygonContact.h                   /usr/include/Box2D/Dynamics/Contacts/b2PolygonContact.h
cp /usr/local/include/Box2D/Dynamics/Contacts/b2TOISolver.h                        /usr/include/Box2D/Dynamics/Contacts/b2TOISolver.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2DistanceJoint.h                      /usr/include/Box2D/Dynamics/Joints/b2DistanceJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2FrictionJoint.h                      /usr/include/Box2D/Dynamics/Joints/b2FrictionJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2GearJoint.h                          /usr/include/Box2D/Dynamics/Joints/b2GearJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2Joint.h                              /usr/include/Box2D/Dynamics/Joints/b2Joint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2LineJoint.h                          /usr/include/Box2D/Dynamics/Joints/b2LineJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2MouseJoint.h                         /usr/include/Box2D/Dynamics/Joints/b2MouseJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2PrismaticJoint.h                     /usr/include/Box2D/Dynamics/Joints/b2PrismaticJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2PulleyJoint.h                        /usr/include/Box2D/Dynamics/Joints/b2PulleyJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2RevoluteJoint.h                      /usr/include/Box2D/Dynamics/Joints/b2RevoluteJoint.h
cp /usr/local/include/Box2D/Dynamics/Joints/b2WeldJoint.h                          /usr/include/Box2D/Dynamics/Joints/b2WeldJoint.h
cp /usr/local/lib/libBox2D.a                                                       /usr/lib/libBox2D.a
cp /usr/local/lib/libBox2D.so.2.1.0                                                /usr/lib/libBox2D.so.2.1.0
cp /usr/local/lib/libBox2D.so                                                      /usr/lib/libBox2D.so
cp /usr/local/lib/libBox2D.a                                                       /usr/lib/libBox2D.a
cp /usr/local/lib/Box2D/Box2D-targets.cmake                                        /usr/lib/Box2D/Box2D-targets.cmake
cp /usr/local/lib/Box2D/Box2D-targets-noconfig.cmake                               /usr/lib/Box2D/Box2D-targets-noconfig.cmake
cp /usr/local/lib/Box2D/Box2DConfig.cmake                                          /usr/lib/Box2D/Box2DConfig.cmake

