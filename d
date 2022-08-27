
bool a=false;
                    while (a==false)
                    {
                        for (int i=0; i<testMap.solid.GetWidth(); ++i)
                        {
                            for (int ii=0; ii<testMap.solid.GetHeight(); ++ii)
                            {
                                if (testMap.solid.GetTile(i, ii).GetGlobalBounds().intersects(player.hitbox))
                                {
                                    player.y+=1.f;
                                    player.sprite.setPosition(player.x, player.y);

                                    player.hitbox.top=player.y;
                                    player.hitbox.left=player.x;
                                    player.hitbox.width=64.f;
                                    player.hitbox.height=64.f;
                                }
                                else
                                {
                                    a=true;
                                }
                            }
                        }
                    }
                }


        if (testMap.solid.GetTile(i, ii).GetGlobalBounds().intersects(player.floor) == true)
            {
                player.collisionDown=true;
                std::cout << "true" << std::endl;
            }
            else if (testMap.solid.GetTile(i, ii).GetGlobalBounds().intersects(player.floor) == false)
            {
                player.collisionDown=false;
                //std::cout << "false" << std::endl;
            }
