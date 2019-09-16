#include <SFML/Graphics.hpp>
#include <time.h>
//
using namespace sf;

class Player
{ // класс Игрока
public:
    float posX, posY, botW, botH, topH, topW, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    int dir = 0;                                                 //направление (direction) движения игрока
    String File;                                                 //файл с расширением
    Image image;                                                 //сфмл изображение
    Texture texture;                                             //сфмл текстура
    Sprite spriteTop, spriteBot;                                 //сфмл спрайт

    Player(String F, float posX, float posY, float botW, float botH) : posX(posX), posY(posY), botW(botW), botH(botH)
    {
        File = F; //имя файла+расширение

        image.loadFromFile(File);
        image.createMaskFromColor(Color(86, 177, 222)); //убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
        texture.loadFromImage(image);                   //закидываем наше изображение в текстуру
        spriteTop.setTexture(texture);
        spriteBot.setTexture(texture);                         //заливаем спрайт текстурой
        spriteBot.setTextureRect(IntRect(0, 618, botW, botH)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
        spriteTop.setTextureRect(IntRect(0, 582, botW, 29));
    }

    void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
    {
        switch (dir) //реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
        case 0:
            dx = speed;
            dy = 0;
            break; //по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
        case 1:
            dx = -speed;
            dy = 0;
            break; //по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
        case 2:
            dx = 0;
            dy = speed;
            break; //по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
        case 3:
            dx = 0;
            dy = -speed;
            break; //по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
        }

        posX += dx * time; //то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
        posY += dy * time; //аналогично по игреку

        speed = 0; //зануляем скорость, чтобы персонаж остановился.
        spriteTop.setPosition(posX, posY - botH);
        spriteBot.setPosition(posX, posY); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    }
};

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(800, 242), "Metal Slug");
    window.setFramerateLimit(60);
    float CurrentFrame = 0; //хранит текущий кадр
    Clock clock;
    Player player1("img/Metal Slug_Tarma.png", 0, 170, 39, 19); //создаем объект p класса player,путь к файлу , далее координата Х,У, ширина, высота.

    Texture t1;
    t1.loadFromFile("img/background.png");
    Sprite sBackground(t1);
    sBackground.setTextureRect(IntRect(469, 3, 4293, 242));

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))))
        {
            player1.dir = 1;
            player1.speed = 0.1; //dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 12)
                CurrentFrame -= 12;
            player1.spriteTop.setTextureRect(IntRect(39 * int(CurrentFrame), 582, -39, 29));
            player1.spriteBot.setTextureRect(IntRect(39 * int(CurrentFrame), 618, -39, 19)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
        }

        if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))
        {
            player1.dir = 0;
            player1.speed = 0.1; //направление вправо, см выше
            CurrentFrame += 0.005 * time;
            if (CurrentFrame > 12)
                CurrentFrame -= 12;
            player1.spriteTop.setTextureRect(IntRect(0 + 39 * int(CurrentFrame), 582, 39, 29));
            player1.spriteBot.setTextureRect(IntRect(0 + 39 * int(CurrentFrame), 618, 39, 19)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
        }

        player1.update(time);
        window.clear();
        window.draw(sBackground);
        window.draw(player1.spriteTop);
        window.draw(player1.spriteBot);
        window.display();
    }

    return 0;
}
