#pragma once
#ifndef ARCHIVETOOL_H
#define ARCHIVETOOL_H

#include <string>
#include <vector>
#include <ostream>

namespace Tool {

    using byte_t = unsigned char;
    class ArchiveTool {
    public:
        /**
         * @description:                      �Ӹ���·����ѹ���ļ�����ȡ�ļ����ݵ�������
         * @param {string&} inArchive         ѹ���ļ�·��
         * @param {vector<byte_t>&} outBuffer �洢�ļ�����
         * @return {*}                        ��outBuffer����
         */
        std::vector<byte_t> extract(const std::string& inArchive, std::vector<byte_t>& outBuffer);
        /**
         * @description:                      ʹ������Ӹ���·����ѹ���ļ�����ȡ�ļ����ݵ�������
         * @param {string&} inArchive         ѹ���ļ�·��
         * @param {vector<byte_t>&} outBuffer �洢�ļ�����
         * @param {string} mPassword          ����ֵ
         * @return {*}                        ��outBuffer����
         */
        std::vector<byte_t> extractWithPassword(const std::string& inArchive, std::vector<byte_t>& outBuffer, std::string mPassword);

        /**
         * @description:                      �������������������ѹ����ʽ���ļ�
         * @param {vector<byte_t>&} outBuffer ��Ҫѹ��������
         * @param {string&} outFile           ѹ���ļ������·��
         * @param {string&} fileName          ѹ���ļ��ڲ����ļ�����������׺��
         * @return {*}
         */
        void compress(const std::vector<byte_t>& buffer, const std::string& outFile, const std::string& fileName);

        /**
         * @description:                      ʹ�����뽫�����������������ѹ����ʽ���ļ�
         * @param {vector<byte_t>&} outBuffer ��Ҫѹ��������
         * @param {string&} outFile           ѹ���ļ������·��
         * @param {string&} fileName          ѹ���ļ��ڲ����ļ�����������׺��
         * @param {string} mPassword          ����ֵ
         * @return {*}
         */
        void compressWithPassword(const std::vector<byte_t>& buffer, const std::string& outFile, const std::string& fileName, std::string mPassword);

        /**
         * @description:                      ʹ�����뽫�����������������ѹ����ʽ���ļ�
         * @param {vector<byte_t>&} outBuffer ��Ҫѹ��������
         * @param {ostream&} outStream        �����
         * @param {string&} fileName          ѹ���ļ��ڲ����ļ�����������׺��
         * @param {string} mPassword          ����ֵ
         * @return {*}
         */
        void compressWithPassword(const std::vector<byte_t>& buffer, std::ostream& outStream, const std::string& fileName, std::string mPassword);

        /**
         * @description:                         ʹ�����뽫�ļ������ݼ���ѹ��Ϊѹ���ļ�
         * @param {vector<std::string>&} inpaths ��Ҫѹ�����ļ�·������
         * @param {ostream&} outStream           �����
         * @param {string&} fileName             ѹ���ļ��ڲ����ļ�����������׺��
         * @param {string} mPassword             ����ֵ
         * @return {*}
         */
        void compressWithPassword(const std::vector<std::string>& inpaths, std::ostream& outStream, const std::string& mPassword);

        /**
         * @description:                         ʹ�����뽫�ļ������ݼ���ѹ��Ϊѹ���ļ�
         * @param {vector<std::string>&} inpaths ��Ҫѹ�����ļ�·������
         * @param {string&} outFile              ���ѹ���ļ���·��
         * @param {string} mPassword             ����ֵ
         * @return {*}
         */
        void compressWithPassword(const std::vector<std::string>& inpaths, const std::string& outFile, const std::string& mPassword);

        /**
         * @description:                      ��string����д��buffer��
         * @param {string&} data              �Զ�������
         * @param {vector<byte_t>&} outBuffer �洢�Զ������ݵĻ�����
         * @return {*}
         */
        std::vector<byte_t> string_to_byte(const std::string& data, std::vector<byte_t>& buffer);

        /**
         * @description:                      ��buffer����ת��Ϊstring
         * @param {vector<byte_t>&} outBuffer ��Ҫת������������
         * @return {*}
         */
        std::string byte_to_string(const std::vector<byte_t>& buffer);
    };
}

#endif 
// MYTOOLS_HPP