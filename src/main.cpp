#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>     // getopt
#include <sys/stat.h>   // stat
#include <vector>


// ディレクトリから取得
#include <sys/types.h>
//#include <cstdlib>
#include <dirent.h>
//#include <sys/stat.h>
//#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

bool parseOption(int argc, char *argv[], std::string *directoryName, double *ratio)
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
                //printf("dirName = %s\n", dirName);
                *directoryName = dirName;
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

bool makeResultDirectory(std::string srcDir, std::string &dstDir, std::string suffix)
{
    struct stat statBuf;

    // src の存在確認
    if (stat(srcDir.c_str(), &statBuf) != 0) {
        std::cout << "srcDir :" << srcDir << " is not found." << std::endl;
        return false;
    }

    // dst の命名
    dstDir = srcDir + suffix;

    // dst 作成
    if (mkdir(dstDir.c_str(), 0775) !=0) {
        std::cout << "Failed to make detDir :" << dstDir << std::endl;
        return false;
    }

    return true;
}

bool getFileList(std::string path, std::vector<std::string> &fileList, std::string extension)
{
	std::string fname;
	std::vector<std::string> cand;

	// ディレクトリへのポインタ
	DIR *dp;

	 // readdir() で返されるエントリーポイント
	dirent* entry;

	dp = opendir(path.c_str());
	if (dp==NULL) return false;

	do {
		// エントリーポイント
		entry = readdir(dp);

		if (entry != NULL) {
			fname = entry->d_name;

			// ファイルの場合
			auto pos1 = fname.find(extension);
			if (pos1 == std::string::npos) continue;

			//fileList.push_back(path+fname);
			fileList.push_back(fname);
		}

	} while (entry != NULL);

	closedir(dp);

	if (fileList.size() <= 0) return false;

	// sort
	std::sort(fileList.begin(), fileList.end());
	return true;
}

bool createResizeImage(std::string srcDir, std::vector<std::string> fileList, std::string dstDir, double ratio)
{
#if 0
    for (const auto& e : fileList){
        std::cout << srcDir << "/" << e << std::endl;

        // オープン
        cv::Mat src = cv::imread(srcDir+"/"+e);

        // 縮小
        cv::resize(src, src, cv::Size(), ratio, ratio);

        // 保存
        cv::imwrite(dstDir+"/"+e, src);
        
        std::cout << "done." << std::endl;
    }
#endif

    for (const auto& e : fileList){
        std::cout << srcDir << "/" << e << std::endl;
        std::string filename = srcDir + "/" + e;

        // 画像ファイルをdstにコピー
        std::string cmd = "cp " + filename + " test_resize";
        system(cmd.c_str());

        // オープン
        cv::Mat src = cv::imread(dstDir+"/"+e);

        // 縮小
        cv::resize(src, src, cv::Size(), ratio, ratio);

        // 保存
        cv::imwrite(dstDir+"/"+e, src);
        
        std::cout << "done." << std::endl;
    }
    

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
    if (!parseOption(argc, argv, &dirNameSrc, &ratio)) return -1;

    // ディレクトリの確認
    //std::cout << "src dir name = " << dirNameSrc << std::endl;

    // 同じ階層に結果ディレクトリの作成
    std::string suffix = "_resize";
    if (!makeResultDirectory(dirNameSrc, dirNameDst, suffix)) return -1;

    // ディレクトリ内のすべてのjpgのファイル名をリスト化
    std::vector<std::string> fileList;
    if (!getFileList(dirNameSrc, fileList, "JPG")) return -1;

    // 縮小処理して保存
    if (!createResizeImage(dirNameSrc, fileList, dirNameDst, ratio)) return -1;

    // このとき、メタ情報も残したいのだができる？

    return 0;
}