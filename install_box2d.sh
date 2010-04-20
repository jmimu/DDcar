#	cd $BOX2DPATH/Build
#	cmake -DBOX2D_INSTALL=ON -DBOX2D_BUILD_SHARED=ON ..
#	make
#	make install

sudo mkdir /usr/include/Box2D/
sudo mkdir /usr/include/Box2D/Collision
sudo mkdir /usr/include/Box2D/Collision/Shapes
sudo mkdir /usr/include/Box2D/Common
sudo mkdir /usr/include/Box2D/Dynamics
sudo mkdir /usr/include/Box2D/Dynamics/Contacts
sudo mkdir /usr/include/Box2D/Dynamics/Joints
sudo mkdir /usr/lib/Box2D/
sudo cp /usr/local/include/Box2D/Box2D.h                                                /usr/include/Box2D.h                                                
sudo cp /usr/local/include/Box2D/Collision/b2BroadPhase.h                               /usr/include/Box2D/Collision/b2BroadPhase.h
sudo cp /usr/local/include/Box2D/Collision/b2Collision.h                                /usr/include/Box2D/Collision/b2Collision.h
sudo cp /usr/local/include/Box2D/Collision/b2Distance.h                                 /usr/include/Box2D/Collision/b2Distance.h
sudo cp /usr/local/include/Box2D/Collision/b2DynamicTree.h                              /usr/include/Box2D/Collision/b2DynamicTree.h
sudo cp /usr/local/include/Box2D/Collision/b2TimeOfImpact.h                             /usr/include/Box2D/Collision/b2TimeOfImpact.h
sudo cp /usr/local/include/Box2D/Collision/Shapes/b2CircleShape.h                       /usr/include/Box2D/Collision/Shapes/b2CircleShape.h
sudo cp /usr/local/include/Box2D/Collision/Shapes/b2PolygonShape.h                      /usr/include/Box2D/Collision/Shapes/b2PolygonShape.h
sudo cp /usr/local/include/Box2D/Collision/Shapes/b2Shape.h                             /usr/include/Box2D/Collision/Shapes/b2Shape.h
sudo cp /usr/local/include/Box2D/Common/b2BlockAllocator.h                              /usr/include/Box2D/Common/b2BlockAllocator.h
sudo cp /usr/local/include/Box2D/Common/b2Math.h                                        /usr/include/Box2D/Common/b2Math.h
sudo cp /usr/local/include/Box2D/Common/b2Settings.h                                    /usr/include/Box2D/Common/b2Settings.h
sudo cp /usr/local/include/Box2D/Common/b2StackAllocator.h                              /usr/include/Box2D/Common/b2StackAllocator.h
sudo cp /usr/local/include/Box2D/Dynamics/b2Body.h                                      /usr/include/Box2D/Dynamics/b2Body.h
sudo cp /usr/local/include/Box2D/Dynamics/b2ContactManager.h                            /usr/include/Box2D/Dynamics/b2ContactManager.h
sudo cp /usr/local/include/Box2D/Dynamics/b2Fixture.h                                   /usr/include/Box2D/Dynamics/b2Fixture.h
sudo cp /usr/local/include/Box2D/Dynamics/b2Island.h                                    /usr/include/Box2D/Dynamics/b2Island.h
sudo cp /usr/local/include/Box2D/Dynamics/b2TimeStep.h                                  /usr/include/Box2D/Dynamics/b2TimeStep.h
sudo cp /usr/local/include/Box2D/Dynamics/b2World.h                                     /usr/include/Box2D/Dynamics/b2World.h
sudo cp /usr/local/include/Box2D/Dynamics/b2WorldCallbacks.h                            /usr/include/Box2D/Dynamics/b2WorldCallbacks.h
sudo cp /usr/local/include/Box2D/Dynamics/Contacts/b2CircleContact.h                    /usr/include/Box2D/Dynamics/Contacts/b2CircleContact.h
sudo cp /usr/local/include/Box2D/Dynamics/Contacts/b2Contact.h                          /usr/include/Box2D/Dynamics/Contacts/b2Contact.h
sudo cp /usr/local/include/Box2D/Dynamics/Contacts/b2ContactSolver.h                    /usr/include/Box2D/Dynamics/Contacts/b2ContactSolver.h
sudo cp /usr/local/include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h          /usr/include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h
sudo cp /usr/local/include/Box2D/Dynamics/Contacts/b2PolygonContact.h                   /usr/include/Box2D/Dynamics/Contacts/b2PolygonContact.h
sudo cp /usr/local/include/Box2D/Dynamics/Contacts/b2TOISolver.h                        /usr/include/Box2D/Dynamics/Contacts/b2TOISolver.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2DistanceJoint.h                      /usr/include/Box2D/Dynamics/Joints/b2DistanceJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2FrictionJoint.h                      /usr/include/Box2D/Dynamics/Joints/b2FrictionJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2GearJoint.h                          /usr/include/Box2D/Dynamics/Joints/b2GearJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2Joint.h                              /usr/include/Box2D/Dynamics/Joints/b2Joint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2LineJoint.h                          /usr/include/Box2D/Dynamics/Joints/b2LineJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2MouseJoint.h                         /usr/include/Box2D/Dynamics/Joints/b2MouseJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2PrismaticJoint.h                     /usr/include/Box2D/Dynamics/Joints/b2PrismaticJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2PulleyJoint.h                        /usr/include/Box2D/Dynamics/Joints/b2PulleyJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2RevoluteJoint.h                      /usr/include/Box2D/Dynamics/Joints/b2RevoluteJoint.h
sudo cp /usr/local/include/Box2D/Dynamics/Joints/b2WeldJoint.h                          /usr/include/Box2D/Dynamics/Joints/b2WeldJoint.h
sudo cp /usr/local/lib/libBox2D.a                                                       /usr/lib/libBox2D.a
sudo cp /usr/local/lib/libBox2D.so.2.1.0                                                /usr/lib/libBox2D.so.2.1.0
sudo cp /usr/local/lib/libBox2D.so                                                      /usr/lib/libBox2D.so
sudo cp /usr/local/lib/libBox2D.a                                                       /usr/lib/libBox2D.a
sudo cp /usr/local/lib/Box2D/Box2D-targets.cmake                                        /usr/lib/Box2D/Box2D-targets.cmake
sudo cp /usr/local/lib/Box2D/Box2D-targets-noconfig.cmake                               /usr/lib/Box2D/Box2D-targets-noconfig.cmake
sudo cp /usr/local/lib/Box2D/Box2DConfig.cmake                                          /usr/lib/Box2D/Box2DConfig.cmake
