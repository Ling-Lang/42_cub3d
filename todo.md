
## TODO

### Hauptziele
* [x] Map parsing
* [x] Basic rendering nur Farben
* [?] Movement
* [ ] Textures
* [ ] Performance


### Bugs

* [ ] Map parsing Segfault fixen bei tabs/leerzeichen nachpfad

---

Notes:
* Nur neu rendern wenn der spieler sich bewegt hat oder umgeschaut hat. (Nach keyhook).


---

MAP:

* wenn eine zelle um sich ein leer hat dann muss es eine wand sein
* es muss genau ein n s w oder e geben

-1 für leerzeichen
0 boden
1 wand
N S W E spieler

-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------

von Robin 13.01.2024 / 23:16 Uhr

Wir müssen unsere Daten in unserm "Ray-Struct" setzen, am Anfang(ausrechnen). Auf dieser Basis werden dann alle weiteren Kalkulationen durchgeführt: nach jedem move des Players, wird "render_raycast" dann frisch ausgeführt, dass kommt aber erst im nächsten Schritt dann. Zuerst mal implementieren :-)

void	render_raycast(t_data *data)

	a.) init_texture_pixels(data);      --> Zweck: Speicher für ein Array von Pixeln für eine Textur initialisieren + wir befüllen unser 2D Array (data-textures) mit einer Farbe. Wenn wir nur 1 Farbe Anfangs verwenden ist es etwas einfacher. Ansonsten gerne schon mit einem texture. So wie du magst Jens.

	b.) init_ray(&data->ray);           --> Zweck: Alle Daten im Struct Ray auf 0 setzen; --> Diese Funktion haben wir schon. Können wir einfach wieder verwenden :-)

	c.) raycasting(&data->player, data);--> Zweck: Wir füllen unseren Struct mit unseren notwendigen Daten (Rechnen!)

	d.) render_frame(data);             --> weiß ich noch nicht :-) Müssen wir zusammen machen :-)

-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------

	Für das ausrechnen verwenden wir dann am besten den Guide von Neosizzle auf GitHub. Da sind alle Formeln drauf die wir brauchen. Das sollte ausreichen.

-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------


    BEISPIELE:
    ----------
    ----------
    c.) int	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;                                --> Einen Struct für unseren Strahlen erzeugen
	
    while (x < data->win_width)                     --> wir iterrieren nun über jede X-Linie bis wir unsere Bildschirmbreite erreicht haben. In unserem Fall (Win-width(320)!). Es wird also von 0 bis 319 durchiterriert.
	{
        init_raycasting_info(x, &ray, player);      --> wir setzen für jede X-Linie einen Wert und machen dies in unserer Extra Funktion init_raycasting_info(x, &ray, player)		 --> (Berechnungen)
		set_dda(&ray, player);                      --> siehe ganz unten
		perform_dda(data, &ray);                    --> siehe ganz unten
		calculate_line_height(&ray, data, player);  --> siehe ganz unten
		update_texture_pixels(data, &data->texinfo, &ray, x); -->s.u.
		x++;                                        --> nächste X-Line wird berechnet
	}
	return (SUCCESS);
}

We initialize the set up for the rays
- camera_x -> Where is the camera (-1 = left, 0 = center, 1 = right)
- dir_x/y = direction of the ray
- map_x/y = current square of the ray
- deltadist_x/y = distance to go to the next x or y.
*/


    WIRD AUFGERUFEN VON FUNKTION RAYCASTING:
    ----------------------------------------
    ----------------------------------------
void	init_raycasting_info(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;                  --> berechnet den Wert von Camera_x (er liegt definitv zw. -1 0 +1)
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;   --> Berechnet die x-Komponente der Richtung des Rays auf der Kameraplane.
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;   --> Berechnet die y-Komponente der Richtung des Rays auf der Kameraplane.
	ray->map_x = (int)player->pos_x;                                --> Pos des Spielers auf Raster also Pos. X
	ray->map_y = (int)player->pos_y;                                --> Pos des Spielers auf Raster also Pos. Y
	ray->deltadist_x = fabs(1 / ray->dir_x);                        --> Berechnet den Betrag der Distanz zwischen den horizontalen Rasterlinien auf der Karte.
	ray->deltadist_y = fabs(1 / ray->dir_y);                        --> Berechnet den Betrag der Distanz zwischen den vertikalen Rasterlinien auf der Karte.
}



Tagesziel für Montag erreicht. Yaay :-) [x]


-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------

Das hier kommt alles später:
wir machen noch Step by Step






Diese Funktion raycasting implementiert den Raycasting-Algorithmus für die Erzeugung einer 3D-ähnlichen Perspektive in einem 2D-Spiel, insbesondere für Spiele im Stil von Wolfenstein 3D. Hier ist eine Übersicht über die Funktion:

Ein t_ray-Objekt wird initialisiert und auf das in der t_data-Struktur gespeicherte ray-Objekt gesetzt. Dieses Objekt wird dazu verwendet, Informationen über den Strahl (Ray) zu speichern.

ray = data->ray;
Eine Schleife über die Breite des Fensters (data->win_width) wird gestartet, um den Raycasting-Algorithmus für jede vertikale Spalte des Bildschirms auszuführen.


while (x < data->win_width)
{
    // Raycasting-Operationen für die Spalte x
    x++;
}


Für jede Spalte wird die Funktion init_raycasting_info aufgerufen, die die Startwerte für den Raycast initialisiert, einschließlich des Winkels und der Startposition.


init_raycasting_info(x, &ray, player);
Die Funktion set_dda wird aufgerufen, um die Digital Differential Analyzer (DDA) für den Raycast einzustellen. DDA wird verwendet, um die Entfernungen der Wände zu berechnen.


set_dda(&ray, player);
Der eigentliche DDA-Algorithmus wird durch die Funktion perform_dda ausgeführt. Diese Funktion berechnet, welche Wand der Ray trifft und die Entfernung zu dieser Wand.


perform_dda(data, &ray);
Die Funktion calculate_line_height wird aufgerufen, um die Höhe der zu zeichnenden Linie zu berechnen, basierend auf der Entfernung zur Wand und der Bildschirmhöhe.


calculate_line_height(&ray, data, player);
Schließlich wird die Funktion update_texture_pixels aufgerufen, um die Texturpixel für die aktuelle Spalte zu aktualisieren. Dies beinhaltet das Mapping der Textur auf die Bildschirmlinie entsprechend dem DDA-Ergebnis.


update_texture_pixels(data, &data->texinfo, &ray, x);
Die Schleife durchläuft alle vertikalen Spalten des Bildschirms und kehrt dann mit return (SUCCESS); zurück.
Zusammengefasst implementiert die raycasting-Funktion den grundlegenden Raycasting-Algorithmus, der verwendet wird, um 3D-ähnliche Szenen auf einem 2D-Bildschirm darzustellen. Der Algorithmus erzeugt eine Perspektive, indem er die Entfernungen von der Kamera zu den Wänden berechnet und Texturierung für realistischere Darstellungen verwendet.




Zum Thema Rendern:
------------------
------------------

Die Funktion render_frame ist verantwortlich für das Rendern eines einzelnen Frames auf dem Bildschirm. Hier ist eine Aufschlüsselung der Funktionalitäten:

t_img image;: Eine Struktur t_img wird deklariert, um Informationen über das Bild zu speichern.

image.img = NULL;: Das Bildobjekt innerhalb der Struktur wird auf NULL gesetzt.

init_img(data, &image, data->win_width, data->win_height);: Die Funktion init_img wird aufgerufen, um das Bild zu initialisieren. Dies könnte das Allokieren von Speicher und das Setzen von Eigenschaften wie Breite, Höhe usw. umfassen.

Eine verschachtelte Schleife wird verwendet, um jeden Pixel des Bildes zu durchlaufen:


y = 0;
while (y < data->win_height)
{
    x = 0;
    while (x < data->win_width)
    {
        set_frame_image_pixel(data, &image, x, y);
        x++;
    }
    y++;
}
In dieser Schleife wird für jeden Pixel auf den Bildschirmkoordinaten (x, y) die Funktion set_frame_image_pixel aufgerufen. Diese Funktion ist verantwortlich für das Setzen des Farbwerts für den entsprechenden Pixel im Bild.

mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);: Das gerenderte Bild wird mithilfe der Funktion mlx_put_image_to_window auf das Fenster (data->win) gezeichnet.

mlx_destroy_image(data->mlx, image.img);: Nachdem das Bild auf das Fenster gezeichnet wurde, wird der zugehörige Speicher freigegeben, um Speicherlecks zu vermeiden. mlx_destroy_image wird verwendet, um das Bildobjekt zu zerstören.

Zusammengefasst erstellt und rendert die Funktion render_frame einen Frame, indem sie jeden Pixel des Bildes festlegt und dann das Bild auf das Fenster zeichnet. Dies ist ein typischer Ablauf in der Computergrafikprogrammierung, insbesondere wenn man mit der MinilibX-Bibliothek arbeitet




--------------------------------------------------
--------------------------------------------------
Eintrag Robin am 15.01.2024 / 23:20 Uhr:				Zustäzlicher Hinweis zur Performance --> siehe Line 193-195
--------------------------------------------------
-------------------------------------------------- 

Thema: Boden und Decke verlegen :-)
------------------------------------

zum einlesen:

Im Gegensatz zu den Wandtexturen sind die Boden- und Deckentexturen horizontal und können daher nicht auf die gleiche Weise gezeichnet werden wie die Wand mit vertikalen Streifen. Stattdessen werden sie mit horizontalen Scanlinien gezeichnet. Die Perspektive ähnelt der von Wänden, ist jedoch um 90 Grad gedreht. Im Gegensatz zu den Wänden, bei denen genau eine Textur pro vertikalen Streifen verwendet wurde, können jedoch mehrere Bodentexturen (oder dieselbe wiederholt) unsere horizontale Linie kreuzen.

Das Zeichnen der Decke erfolgt auf die gleiche Weise wie das Zeichnen des Bodens, daher wird hier nur der Boden erklärt.

Der Bodenguss erfolgt "vor"!!! den Wänden, also zeichnen wir zunächst den "gesamten Boden" (und die Decke) und überschreiben dann im nächsten Schritt wie zuvor einen Teil der Pixel mit den Wänden.

Kurz gesagt funktioniert der Bodenguss wie folgt: Scanline für Scanline vorgehen. Berechnen Sie für die aktuelle Scanlinie die Position auf dem Boden, die dem linken Pixel der Scanlinie entspricht, und die Position, die dem rechten Pixel entspricht. Dies kann dadurch berechnet werden, dass der Strahl, der von der Kamera ausgeht und durch dieses Pixel der Kameraebene geht, auf den Boden trifft. Die Formeln und Erläuterungen hierzu finden wir weiter unten im Code zum Verlegen von Böden.

Wir können dann zwischen diesem Punkt ganz links und ganz rechts linear interpolieren, um die Bodenkoordinaten zu erhalten, die mit den anderen Pixeln dieser Scanlinie übereinstimmen. Das funktioniert, weil die Bodenstruktur perfekt horizontal ist.

Jetzt kommt der neue Bodengusscode, der Zeile für Zeile statt vertikaler Streifen für vertikaler Streifen vorgeht.
Die Formel für rowDistance, den horizontalen Abstand von der Kamera zum Boden für die aktuelle Reihe, der posZ / p ist, wobei p der aktuelle Pixelabstand von der Bildschirmmitte ist, kann wie folgt erklärt werden:

Der Kamerastrahl geht durch die folgenden zwei Punkte: die Kamera selbst, die sich auf einer bestimmten Höhe (posZ) befindet, und einen Punkt vor der Kamera (durch eine gedachte vertikale Ebene, die die Bildschirmpixel enthält) mit horizontalem Abstand 1 von der Kamera und die vertikale Position p niedriger als posZ (posZ - p). Beim Durchlaufen dieses Punktes ist die Linie vertikal um p Einheiten und horizontal um 1 Einheit zurückgelegt worden. Um den Boden zu erreichen, muss es stattdessen PosZ-Einheiten zurücklegen. Es bewegt sich horizontal im gleichen Verhältnis. Das Verhältnis betrug 1/p für den Durchgang durch die Kameraebene. Wenn wir also posZ-mal weiter gehen, um den Boden zu erreichen, beträgt die gesamte horizontale Distanz posZ/p.

HINWEIS: Das hier durchgeführte Stepping ist eine affine Texturzuordnung, was bedeutet, dass wir linear zwischen zwei Punkten interpolieren können, anstatt für jedes Pixel eine andere Unterteilung berechnen zu müssen. Dies ist im Allgemeinen nicht perspektivisch korrekt, aber für perfekt horizontale Böden/Decken (und auch perfekt vertikale Wände) ist es so, sodass wir es für Raycasting verwenden können.



//BODENGUSS

     for(int y = 0; y < h; y++)
    {
      // rayDir für den Strahl ganz links (x = 0) und den Strahl ganz rechts (x = w)
    	float rayDirX0 = dirX - planeX;
      float rayDirY0 = dirY - planeY;
      float rayDirX1 = dirX + planeX;
      float rayDirY1 = dirY + planeY;

      // Aktuelle y-Position im Vergleich zur Mitte des Bildschirms (dem Horizont)
       int p = y - screenHeight / 2;

      // Vertikale Position der Kamera.
      float posZ = 0,5 * screenHeight;

      // Horizontaler Abstand von der Kamera zum Boden für die aktuelle Reihe.
      // 0,5 ist die Z-Position genau in der Mitte zwischen Boden und Decke.
      float rowDistance = posZ / p;

      // Berechnen Sie den realen Schrittvektor, den wir für jedes x hinzufügen müssen (parallel zur Kameraebene)
       // Schrittweises Addieren vermeidet Multiplikationen mit einem Gewicht in der inneren Schleife
       float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

      // reale Koordinaten der Spalte ganz links. Dies wird aktualisiert, wenn wir nach rechts gehen.
      float floorX = posX + rowDistance * rayDirX0;
      float floorY = posY + rowDistance * rayDirY0;

      for(int x = 0; x < screenWidth; ++x)
      {
        // die Zellkoordinate wird einfach aus den ganzzahligen Teilen von floorX und floorY ermittelt
         int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        // Texturkoordinate aus dem Bruchteil erhalten
         int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
        int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

        floorX += floorStepX;
        floorY += floorStepY;

        // Textur auswählen und Pixel zeichnen
         int floorTexture = 3;
        int Deckentextur = 6;
        Uint32-Farbe;

        //
         Bodenfarbe = Textur[floorTexture][texWidth * ty + tx];
        Farbe = (Farbe >> 1) & 8355711; // etwas dunkler machen
         buffer[y][x] = color;

        //Decke (symmetrisch, bei screenHeight - y - 1 statt y)
         color = texture[ceilingTexture][texWidth * ty + tx];
        Farbe = (Farbe >> 1) & 8355711; // etwas dunkler machen
         buffer[screenHeight - y - 1][x] = color;
      }
    }