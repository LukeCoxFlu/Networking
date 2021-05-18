//collision
       /* float R = 22;
        for (int i = 0; i < numberOfCars; i++)
            for (int j = 0; j < numberOfCars; j++)
            {
                if (i == j) {
                    break;
                }
                int dx = 0, dy = 0;
                while (dx * dx + dy * dy < 4 * R * R)
                {
                    car[i].x += dx / 10.0;
                    car[i].x += dy / 10.0;
                    car[j].x -= dx / 10.0;
                    car[j].y -= dy / 10.0;
                    dx = car[i].x - car[j].x;
                    dy = car[i].y - car[j].y;
                    if (!dx && !dy) break;
                }
            }*/

            //Avoid Player 
            //for (int i = 1; i < numberOfCars; i++) car[i].findTarget(); //SERVER