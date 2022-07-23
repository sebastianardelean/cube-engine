#pragma once

namespace cubeexcept {

    class SdlException: public std::exception {
    public:
        SdlException(const std::string &msg) {
            s_Msg = msg;
        }

        const char *what() const throw() {
            return s_Msg.c_str();
        }

    private:
        std::string s_Msg;
    };

    class SdlCreateWindowException : public SdlException {
    public:
        SdlCreateWindowException(const std::string &msg):SdlException(msg) {

        }

    };

    class SdlRendererCreateException : public SdlException {
    public:
        SdlRendererCreateException(const std::string &msg):SdlException(msg) {

        }


    };
    class SdlTextureCreateException : public SdlException {
    public:
        SdlTextureCreateException(const std::string &msg):SdlException(msg) {

        }


    };

    class SdlSurfaceCreateException : public SdlException {
    public:
        SdlSurfaceCreateException(const std::string &msg):SdlException(msg) {

        }


    };

    class SdlLoadBmpException : public SdlException {
    public:
        SdlLoadBmpException(const std::string &msg):SdlException(msg) {

        }


    };
}