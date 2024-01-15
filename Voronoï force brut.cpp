#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace cv;
using namespace std;

//Nombre de germes modifiables (nombre de formes géométriques dans l'image)
int nombreGermes = 700;

//Renvoie la distance euclidienne entre deux points p1 et p2
double distance(Point2i p1, Point2i p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

//Renvoie l'indice du germe le plus proche dans le tableau de germes pour un pixel donné
int trouverPointLePlusProche(const vector<Point2i>& germes, Point2i pixel) {
    double minDistance = distance(germes[0], pixel);
    int indicePlusProche = 0;

    for (size_t i = 1; i < germes.size(); ++i) {
        double d = distance(germes[i], pixel);
        if (d < minDistance) {
            minDistance = d;
            indicePlusProche = i;
        }
    }

    return indicePlusProche;
}

//Calcul le diagramme de Voronoi discret avec des germes aléatoires
Mat diagrammeVoronoiForceBrute(int largeurImage, int hauteurImage, int nombreGermes, vector<Point2i>& germes) {
    Mat image(hauteurImage, largeurImage, CV_8UC3, Scalar(255, 255, 255));

    
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < nombreGermes; ++i) {
        germes.emplace_back(rand() % largeurImage, rand() % hauteurImage);
    }

    for (int y = 0; y < hauteurImage; ++y) {
        for (int x = 0; x < largeurImage; ++x) {
            int pointLePlusProche = trouverPointLePlusProche(germes, Point2i(x, y));
            Vec3b& couleurPixel = image.at<Vec3b>(y, x);
            couleurPixel = Vec3b(germes[pointLePlusProche].y % 256, germes[pointLePlusProche].x % 256, 0);
        }
    }

    return image;
}

//Appliquer le diagramme de Voronoi discret à l'image en paramètre
Mat approximerImageParVoronoi(const Mat& imageOriginale, const vector<Point2i>& germes) {
    Mat imageApprox = imageOriginale.clone();
    vector<Vec3f> couleursRegion(germes.size(), Vec3b(0, 0, 0));
    vector<int> nombrePixelsRegion(germes.size(), 0);

    //Calcul du total de couleur de chaque région
    for (int y = 0; y < imageOriginale.rows; ++y) {
        for (int x = 0; x < imageOriginale.cols; ++x) {
            int pointLePlusProche = trouverPointLePlusProche(germes, Point2i(x, y));
            Vec3f pixelCouleur(imageOriginale.at<Vec3b>(y, x));
            couleursRegion[pointLePlusProche] += pixelCouleur;
            nombrePixelsRegion[pointLePlusProche]++;
        }
    }

    //Division du total par le nombre de pixel de chaque région pour obtenir la moyenne
    for (size_t i = 0; i < germes.size(); ++i) {
        if (nombrePixelsRegion[i] > 0) {
            couleursRegion[i] /= static_cast<float>(nombrePixelsRegion[i]);
        }
    }

    //Appliquer à chaque pixel la couleur moyenne de sa région
    for (int y = 0; y < imageOriginale.rows; ++y) {
        for (int x = 0; x < imageOriginale.cols; ++x) {
            int pointLePlusProche = trouverPointLePlusProche(germes, Point2i(x, y));          
            imageApprox.at<Vec3b>(y, x) = couleursRegion[pointLePlusProche];
        }
    }

    imageApprox.convertTo(imageApprox, CV_8UC3);  // Conversion vers le type d'image initial

    return imageApprox;
}

int main() {
    // Charger une image existante (vous pouvez utiliser votre propre image)
    Mat imageOriginale = imread("./images/riolu_ruban1.png");

    // Vérifier si l'image est chargée avec succès
    if (imageOriginale.empty()) {
        cerr << "Erreur lors du chargement de l'image." << endl;
        return -1;
    }

    // Taille de l'image et nombre de germes
    int largeurImage = imageOriginale.cols;
    int hauteurImage = imageOriginale.rows;
    

    //Initialisation du tableau de germes
    vector<Point2i> germes;

    // Générer le diagramme de Voronoi
    Mat resultat = diagrammeVoronoiForceBrute(largeurImage, hauteurImage, nombreGermes, germes);

    // Approximer l'image originale
    Mat imageApprox = approximerImageParVoronoi(imageOriginale, germes);

    // Afficher les images
    imshow("Image Originale", imageOriginale);
    imshow("Diagramme de Voronoi", resultat);
    imshow("Approximation par Voronoi", imageApprox);
    imwrite("./images/riolu_ruban_lowpoly2.png", imageApprox);
    waitKey(0);

    return 0;
}
