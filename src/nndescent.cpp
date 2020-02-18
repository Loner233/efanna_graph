//
// Created by 付聪 on 2017/6/21.
//

#include <efanna2e/index_graph.h>
#include <efanna2e/index_random.h>
#include <efanna2e/util.h>
#include <string>

extern "C" {
void load_data(char *filename, float *&data, unsigned &num, unsigned &dim) {// load data with sift10K pattern
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        std::cout << "open file error" << std::endl;
        exit(-1);
    }
    in.read((char *) &dim, 4);
    std::cout << "data dimension: " << dim << std::endl;
    in.seekg(0, std::ios::end);
    std::ios::pos_type ss = in.tellg();
    size_t fsize = (size_t) ss;
    num = (unsigned) (fsize / (dim + 1) / 4);
    data = new float[num * dim * sizeof(float)];

    in.seekg(0, std::ios::beg);
    for (size_t i = 0; i < num; i++) {
        in.seekg(4, std::ios::cur);
        in.read((char *) (data + i * dim), dim * 4);
    }
    in.close();
}
void foo(char *data_file, char *save_graph, int K, int L, int iter, int S, int R) {
    std::cout << data_file << std::endl;
    std::cout << save_graph << std::endl;
    float *data_load = NULL;
    unsigned points_num, dim;
    load_data(data_file, data_load, points_num, dim);
    char *graph_filename = save_graph;
    //data_load = efanna2e::data_align(data_load, points_num, dim);//one must align the data before build
    efanna2e::IndexRandom init_index(dim, points_num);
    efanna2e::IndexGraph index(dim, points_num, efanna2e::L2, (efanna2e::Index *) (&init_index));

    efanna2e::Parameters paras;
    paras.Set<unsigned>("K", K);
    paras.Set<unsigned>("L", L);
    paras.Set<unsigned>("iter", iter);
    paras.Set<unsigned>("S", S);
    paras.Set<unsigned>("R", R);

    auto s = std::chrono::high_resolution_clock::now();
    index.Build(points_num, data_load, paras);
    auto e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = e - s;
    std::cout << "Time cost: " << diff.count() << "\n";

    index.Save(graph_filename);
}
}

