
## TODO

### Hauptziele
* [x] Map parsing
* [x] Basic rendering nur Farben
* [?] Movement
* [x] Textures
* [x] Performance


### Bugs

* [ ] Map parsing Segfault fixen bei tabs/leerzeichen nachpfad
* [ ] Leaks fixen
* [ ] Funktionen runterbrechen
* [ ] Bonus vielleicht.

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




Zum Thema Rendern: fuer Mittwoch den 17.01.2024:
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




-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------
Mittwoch 17. Jan 2024 / 14:30 Uhr:
-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------

Vorschlag von Copilot Workspace:
--------------------------------




void update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{

```c
void update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
```
Die Funktion nimmt vier Parameter: `data` enthält allgemeine Daten und Einstellungen, `tex` enthält Informationen über die Textur, `ray` enthält Informationen über den Strahl und `x` ist die x-Koordinate des Pixels, das aktualisiert werden soll.

```c
{
    int y;
    int color;
```
Zwei lokale Variablen werden deklariert: `y` ist die y-Koordinate des Pixels, das aktualisiert werden soll, und `color` ist die Farbe, die auf das Pixel angewendet werden soll.

```c
    ft_get_side(data, ray); // Use your function to get the texture index
```
Die Funktion `ft_get_side` wird aufgerufen, um den Index der Textur zu bestimmen, die auf der Seite der Wand angezeigt werden soll, auf die der Strahl trifft.

```c
    tex->x = (int)(ray->wall_x * (double)(tex->size));
```
Die x-Koordinate des Texturpixels wird berechnet, indem die x-Koordinate der Wand, auf die der Strahl trifft, mit der Größe der Textur multipliziert und das Ergebnis in einen Integer umgewandelt wird.

```c
    if ((ray->side == 0 && ray->dir_x > 0)
        || (ray->side == 1 && ray->dir_y < 0))
        tex->x = tex->size - tex->x - 1;
```
Wenn der Strahl in eine bestimmte Richtung zeigt, wird die x-Koordinate des Texturpixels umgekehrt.

```c
    tex->step = tex->size / ray->line_height;
```
Der Schritt, mit dem durch die Textur gelaufen wird, wird berechnet, indem die Größe der Textur durch die Höhe der Linie geteilt wird.

```c
    tex->pos = (ray->draw_start - WIN_HEIGHT / 2
            + ray->line_height / 2) * tex->step;
```
Die Anfangsposition in der Textur wird berechnet.

```c
    y = ray->draw_start;
    while (y < ray->draw_end)
```
Eine Schleife wird gestartet, die von der Anfangs- bis zur Endposition des Strahls läuft.

```c
    {
        tex->y = (int)tex->pos & (tex->size - 1);
        tex->pos += tex->step;
```
In jedem Durchlauf der Schleife wird die y-Koordinate des Texturpixels berechnet und die Position in der Textur wird um den Schritt erhöht.

```c
        color = data->textures[data->texinfo.side].pixels[tex->size * tex->y + tex->x];
```
Die Farbe des Pixels wird aus der Textur abgerufen.

```c
        if (data->texinfo.side == NORTH || data->texinfo.side == EAST)
            color = (color >> 1) & 8355711;
```
Wenn die Textur auf der Nord- oder Ostseite angezeigt wird, wird die Farbe gedimmt.

```c
        if (color > 0)
            data->texture_pixels[y * WIN_WIDTH + x] = color;
```
Wenn die Farbe größer als 0 ist, wird das Pixel in der Textur auf diese Farbe gesetzt.

```c
        y++;
    }
}
```



HIER NOCHMAL DIE GESAMTE FUNKTION:


void update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
    int y;
    int color;

    ft_get_side(data, ray); // Use your function to get the texture index
    tex->x = (int)(ray->wall_x * (double)(tex->size));
    if ((ray->side == 0 && ray->dir_x > 0)
        || (ray->side == 1 && ray->dir_y < 0))
        tex->x = tex->size - tex->x - 1;
    tex->step = 1.0 * tex->size / ray->line_height;
    tex->pos = (ray->draw_start - WIN_HEIGHT / 2
            + ray->line_height / 2) * tex->step;
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        tex->y = (int)tex->pos & (tex->size - 1);
        tex->pos += tex->step;
        color = data->textures[data->texinfo.side][tex->size * tex->y + tex->x];
        if (data->texinfo.side == NORTH || data->texinfo.side == EAST)
            color = (color >> 1) & 8355711;
        if (color > 0)
            data->texture_pixels[y * WIN_WIDTH + x] = color;
        y++;
    }
}

-------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------
-----------------------------------------------------

nach raycast in unserer Funktion "render_main.c"
-->
danach weiter mit "render_frame(data)" !
-->

-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------

Die Funktion `render_frame(t_data *data)` ist dafür verantwortlich, ein Bild (Frame) zu rendern und es auf das Fenster zu zeichnen. Hier ist eine Schritt-für-Schritt-Erklärung:

```c
static void	render_frame(t_data *data)
{
    t_img	image;
    int		x;
    int		y;
```
Die Funktion beginnt mit der Deklaration von drei lokalen Variablen: `image` ist ein `t_img`-Objekt, das das zu rendernde Bild repräsentiert, `x` und `y` sind Koordinaten, die zum Durchlaufen jedes Pixels im Bild verwendet werden.

```c
    image.img = NULL;
    init_img(data, &image, data->win_width, data->win_height);
```
Das `image`-Objekt wird initialisiert mit der Funktion `init_img`, die die Breite und Höhe des Fensters als Parameter erhält.

```c
    y = 0;
    while (y < data->win_height)
    {
        x = 0;
        while (x < data->win_width)
        {
```
Zwei verschachtelte Schleifen werden gestartet, um durch jedes Pixel im Bild zu laufen.

```c
            set_frame_image_pixel(data, &image, x, y);
```
Die Funktion `set_frame_image_pixel` wird aufgerufen, um das Pixel an der Position `(x, y)` im Bild zu setzen. Diese Funktion nimmt die Daten, das Bild und die Koordinaten als Parameter.

```c
            x++;
        }
        y++;
    }
```
Die x- und y-Koordinaten werden erhöht, um das nächste Pixel zu erreichen.

```c
    mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
```
Die Funktion `mlx_put_image_to_window` wird aufgerufen, um das gerenderte Bild auf das Fenster zu zeichnen. Diese Funktion nimmt den MLX-Zeiger, das Fenster und das Bild als Parameter.

```c
{
    mlx_destroy_image(data->mlx, image.img);
}
```
Schließlich wird die Funktion `mlx_destroy_image` aufgerufen, um das Bild zu löschen und Speicher freizugeben. Diese Funktion nimmt den MLX-Zeiger und das Bild als Parameter.

Bitte beachten Sie, dass die Funktionen `init_img` und `set_frame_image_pixel` in Ihrem Code definiert sein müssen. Die genaue Implementierung dieser Funktionen hängt von den Details Ihres Projekts ab.


----------------------------------
HIER NOCHMAL DIE GESAMTE FUNKTION:
----------------------------------

```c 
static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
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
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}
```

------------------------------------------------------------------
UND HIER NOCH EINE KOPIE DER FUNKTION 'SET_FRAME_IMAGE_PIXEL'
------------------------------------------------------------------
```c
static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}
```
