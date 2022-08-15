#ifndef SURFACEANDSTYLESETUP_H
#define SURFACEANDSTYLESETUP_H

#include <QSurfaceFormat>
#include <QFontDatabase>
#include <QQuickStyle>

void setupSurfaceAndStyle()
{
    QSurfaceFormat format;
    format.setSamples(20);
    QSurfaceFormat::setDefaultFormat(format);
    QQuickStyle::setStyle("Material");
    QFontDatabase::addApplicationFont(":/Fonts/Inconsolata.otf");
}

#endif // SURFACEANDSTYLESETUP_H
