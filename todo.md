
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