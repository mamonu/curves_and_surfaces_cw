#include "Attribute.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace TransferableSkills {

    //------------------------------------------------------------------------------
    // constants

    const GLfloat MATERIAL_COLOUR[] = {1.0, 1.0, 1.0, 1.0};
    const GLfloat MATERIAL_SPECULAR[] = {1.0, 1.0, 1.0, 1.0};
    const GLfloat MATERIAL_SHININESS[] = {50.0};
    const GLfloat MATERIAL_EMISSION[] = {0.0, 0.0, 0.0, 0.0};

    //------------------------------------------------------------------------------
    // class definition

    class Material {

    public:

        Material() : _colour(MATERIAL_COLOUR), _specular(MATERIAL_SPECULAR),
                     _shininess(MATERIAL_SHININESS), _emission(MATERIAL_EMISSION) {}
        ~Material() {}
        friend istream &operator>>(istream &in, Material &material);

    private:

        Attribute<GLfloat, 4> _colour;
        Attribute<GLfloat, 4> _specular;
        Attribute<GLfloat, 1> _shininess;
        Attribute<GLfloat, 4> _emission;
        void read(istream &in);

    };

} // TransferableSkills

#endif // Material_h

//------------------------------------------------------------------------------
