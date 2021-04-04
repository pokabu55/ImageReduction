#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

bool parseOption(int argc, char *argv[], std::string directoryName, double *ratio)
{
    int i, opt;
    char *dirName = nullptr;
    //double ratio = 0.27;

    opterr = 0; //getopt()のエラーメッセージを無効にする。

    while ((opt = getopt(argc, argv, "d:r:m")) != -1) {
        //コマンドライン引数のオプションがなくなるまで繰り返す
        switch (opt) {
            case 'd':
                // ディレクトリ名指定のオプション
                dirName = optarg;
                //printf("-d がオプションとして渡されました\n");
                printf("dirName = %s\n", dirName);
                break;

// TODO: まだ使わないオプション
#if 0
            case 'r':
                // リサイズ比指定のオプション
                //printf("-r オプションとして渡されました\n");
                *ratio = atof(optarg);
                printf("ratio = %f\n", *ratio);
                break;
#endif
            case 'm':
                // マニュアル表示のオプション
                //printf("-m オプションとして渡されました\n");
                printf("-r：縮小率を指定するオプション：-r 0.5 と入力する\n");
                printf("-d：処理対象のディレクトリを指定するオプション：-d ./aa と入力する\n\n");
                break;

            default: /* '?' */
                //指定していないオプションが渡された場合
                printf("Usage: %s [-d] [-m argment] arg1 ...\n", argv[0]);
                break;
        }
    }

    //オプション以外の引数を出力する
    for (i = optind; i < argc; i++) {
        printf("arg = %s\n", argv[i]);
    }

    return true;
}

bool makeResultDirectory(std::string srcDir, std::string dstDir)
{
    return true;
}

int main (int argc, char *argv[])
{
    // 縮小率：現状、縮小率は固定とする
    double ratio = 0.27;
    // 引数として、ディレクトリ名を取る
    std::string dirNameSrc = "";
    std::string dirNameDst = "";

    // オプション解析
    if (!parseOption(argc, argv, dirNameSrc &ratio)) return -1;

    // ディレクトリの確認
    std::cout << dirNameSrc << std::endl;


    // 同じ階層に結果ディレクトリの作成
    if (!makeResultDirectory(dirNameSrc, dirNameDst))

    // ディレクトリ内のすべてのjpgのファイル名をリスト化

    // 縮小処理して保存

    // このとき、メタ情報も残したいのだができる？

    return 0;
}